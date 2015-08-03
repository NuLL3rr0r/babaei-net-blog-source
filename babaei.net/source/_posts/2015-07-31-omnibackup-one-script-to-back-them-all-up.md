title: 'OmniBackup: One Script to back them all up'
date: 2015-07-31 23:23:23
tags:
- Backup
- FreeBSD
- GNU
- Linux
- OmniBackup
- Unix
---

A few days ago was _[System Administrator Appreciation Day](http://sysadminday.com/)_. It is celebrated on the last _Friday_ in _July_ and it has been celebrated since _July 28, 2000_. But, system administrators know not all days are like today. They face many hard times and struggles during their careers and the worse of them all is either a [security breech](/blog/2015/07/30/freebsd-block-brute-force-attacks-using-sshguard-and-ipfw-firewall/) or data loss.

For so many years I've been writing and maintaining backup scripts on and on, for every single database I added, for every single directory with critical data, or any other service I was running on every new server I got my hands on. In the end, I found myself ended up in a pile of backup scripts and multitudinous cron entries which was a nightmare to keep track of. I even had to manage the schedule so that two backup scripts do not run at the same time. Even more, I had to manually track the backups whether they were successful or not. Also, someone has to delete the old ones to make rooms for the next ones.

Therefore, I came up with an elegant solution to replace the old process which I found exceptionally error-prone. I call it [OmniBackup](https://gitlab.com/NuLL3rr0r/omnibackup/). At last, I'm able to keep abreast of all the ever-growing data that I have to keep safe, confidently.

"So, what exactly is OmniBackup?" you may ask. That's a fair question. OmniBackup is a [MIT licensed](http://opensource.org/licenses/MIT) [Bash](http://www.gnu.org/software/bash/) script which delivers the following set of features:

* Configuration and customization of backup mechanism through [JSON](http://json.org/)
* Support for [OpenLDAP](http://www.openldap.org/) backups
* Support for [PostgreSQL](http://www.postgresql.org/) backups as a whole or per database
* Support for [MariaDB](https://mariadb.org/) and [MySQL](https://www.mysql.com/) backups as a whole or per database
* Support for filesystem backups with optional ability to follow symbolic links
* Support for running custom scripts with custom arguments with the ability to backup and automatic clean-up of a specific path as the script output which allows extending it for many different customized backup scenarios
* Custom backup file name tagging, e.g. include date or host name
* Online backup without a prerequisite to suspend any service
* Support for backup tasks priority order
* Support for multiple backup servers
* Ability to always keep a copy of backups offline
* Ability to keep a copy of backups offline if no backup server is available, or in case of error such as a file transfer error
* Secure file transfer through SSH / SCP protocol
* LZMA2, [gzip](http://www.gzip.org/) and [bzip2](http://www.bzip.org/) compression algorithms along with different compression levels
* Ability to preserve permissions inside backup files
* Support for symmetric cryptography algorithms AES-128, AES-192 and AES-256 (a.k.a Rijndael or Advanced Encryption Standard)
* Random passphrase generation for encrypted backups with variable length and patterns or a unique passphrase for all backups
* Support for RSA signatures to verify the backup origin and integrity
* Passphrase encryption using RSA public keys for individual backup servers
* Backup integrity verification by offering hash algorithm such as MD4, MD5, MDC-2, RIPEMD160, SHA, SHA-1, SHA-224, SHA-256, SHA-384, SHA-512 and WHIRLPOOL
* Base64 encoding
* Reporting through email to a list of recipients with ability to include passphrases
* Customized mail subject for successful and failed backup operations
* Customized support message for reports
* [Crontab](http://crontab.org/) integration
* Custom temporary / working directory
* Automatic clean-up ability
* An example configuration file in JSON format to get you up and running

There is also a list of planned features and TODOs which did not make it into <code>0.1.0</code> release:

* Restore script
* [GnuPG](https://www.gnupg.org/) integration
* SFTP and FTP support
* Refactoring and code clean-up
* Any potential bug fixes

**_Disclaimer_**: Please be wary of the fact that this script has <code>3.3 K</code> lines of Bash code and devoured hell of a time from me to write and debug. You should also consider that this is my first heavy Bash experiment and I may not write quality code in the language since I'm a newcomer to Bash. I do not claim this OmniBackup is production ready, that's why I did version the first release at <code>0.1.0</code>. Also keep in mind that OmniBackup heavily relies on 3rd-party software which increase the chance for fatal bugs, therefore losing data. So, I provide OmniBackup without any warranties, guarantees or conditions, of any kind and I accept no liability or responsibility any misuse or damages. Please use it at your own risk and remember you're solely responsible for any resulting damage or data loss.

**_Credits_**: Special thanks go to my fellow and long-time friend, _Morteza Sabetraftar_ for his help and ideas without whom OmniBackup lacked features or quality.

Please, feel free to clone and modify it as you wish. Pull requests for new features, improvements or bug fixes are also very welcome.

* [OmniBackup on GitLab](https://gitlab.com/NuLL3rr0r/omnibackup/)
* [OmniBackup on GitHub](https://github.com/NuLL3rr0r/omnibackup/)

The rest of this post serves as a comprehensive guide on how to setup OmniBackup in order to backup and restore all your critical data in a production environment.

<!-- more -->

<br />

### Contents ###

* [Message Types and Their Meanings](#MessageTypes)  
* [Requirements](#Requirements)  
* [Installation](#Installation)  
* [Configuring Temporary Directory](#ConfigTempDirectory)  
* [Configuring Compression](#ConfigCompression)  
* [Configuring Security](#ConfigSecurity)  
* [Configuring Reports](#ConfigReports)  
* [Configuring Remote Backup Servers](#ConfigRemoteBackupServers)  
* [Configuring Backup Tasks](#ConfigBackupTasks)  
* [Configuring Backup Priority and Order](#ConfigBackupPriorityOrder)  
* [Configuring OpenLDAP Backups](#ConfigOpenLdapBackups)  
* [Configuring Database Backups](#ConfigDatabaseBackups)  
* [Configuring PostgreSQL Database Backups](#ConfigPostgreSqlBackups)  
* [Configuring MariaDB and MySQL Databases Backups](#ConfigMariaDbMySqlBackups)  
* [Configuring Filesystem Backups](#ConfigFilesystemBackups)  
* [Configuring Other Backups](#ConfigOtherBackups)  
* [3rd-party Commands status codes](#Config3rdPartyStatusCode)  
* [First Run](#FirstRun)  
* [Crontab](#Crontab)  
* [Source Code](#SourceCode)  


<br />
<a name="MessageTypes"></a>

### Message Types and Their Meanings ###

Before we go any further, you may want to know that other than regular logs there are different kind of messages in OmniBackup which may appear on screen, system logs or mail reports:

* <code>DEBUG</code> it's for development purpose only, so you should not see any message of this kind.
* <code>ERROR</code> some error happened, but the program is able to continue.
* <code>FATAL</code> indicates that something went south due to unrecoverable errors and the program terminates immediately.
* <code>INFO</code> informational notices to inform you about regular events inside the program.
* <code>SUCCESS</code> indicates an operation has been successful.
* <code>TRACE</code> it's for development purpose only, so you should not see any message of this kind.
* <code>WARNING</code> indicates that some situation might happen or already happened which is not desired.


<br />
<a name="Requirements"></a>

### Requirements ###

For now OmniBackup officially only supports [FreeBSD](https://www.freebsd.org/) since all my servers and desktop instances at both home and work are running FreeBSD. This does not mean official support for [GNU](http://www.gnu.org/)/[Linux](https://www.kernel.org/) won't arrive any time soon in the near future. In fact I used to be a heavy [Funtoo](http://www.funtoo.org/) user and even before that [Gentoo](https://www.gentoo.org/). These days I only have a [Slackware](http://www.slackware.com/) instance which I use for cross-compiling C++ libraries to [Android](https://www.android.com/). So, it's just a matter of time before official support arrives. In my estimation, the current code should work out of the box inside any GNU/Linux distribution since I tried my best to write it in a platform-independent manner by reading pile of man pages. I assume if it works on FreeBSD it should also work on other BSDs and GNU/Linuxes. But I'm only 99.99% sure and when it comes to programming computers 0.01% human error is really too much and risky. So, before I announce GNU/Linux support official I must test it at least once. But until that moment comes, I really appreciate feedbacks and possible patches or pull-requests.

Aside from Bash, OmniBackup requires other tools and utilities. Although most of these programs are found in a base installation of your operating system, it relies on a few other programs which has to be installed before we continue. Note that if OmniBackup cannot find a program it gives you a fatal error message and exits.

Requirements for OmniBackup include:

* <code>basename</code>
* <code>bzip2</code>
* <code>caller</code>
* <code>cat</code>
* <code>cd</code>
* <code>cut</code>
* <code>date</code>
* <code>dirname</code>
* <code>du</code>
* <code>echo</code>
* <code>expr</code>
* <code>flock</code>
* <code>grep</code>
* <code>gzip</code>
* <code>head</code>
* <code>hostname</code>
* <code>jq</code>
* <code>logger</code>
* <code>mail</code>
* <code>mkdir</code>
* <code>mysqldump</code>
* <code>openssl</code>
* <code>pg_dump</code>
* <code>pg_dumpall</code>
* <code>printf</code>
* <code>readlink</code>
* <code>rm</code>
* <code>scp</code>
* <code>slapcat</code>
* <code>ssh</code>
* <code>strings</code>
* <code>sudo</code>
* <code>tar</code>
* <code>tr</code>
* <code>xz</code>

I should add, not all of the above dependencies are required in order for OmniBackup to work. At runtime, it dynamically decides which dependencies are required and then search for them. For example, if you did not enabled PostgreSQL database backup, it won't look for <code>pg_dump</code>, <code>pg_dumpall</code> and <code>sudo</code> binaries. Or, if you choose to go with LZMA2 compression algorithm it only looks for <code>xz</code> and ignore both <code>bzip2</code> and <code>xz</code> binaries. Of course some of these commands like <code>cd</code> are internal and there is no need to lookup the filesystem to find them. On my FreeBSD system I only had to install the following ports in order to have all the dependencies complete:

<code>databases/postgresql9*-client</code> one of these ports provide <code>pg_dump</code> and <code>pg_dumpall</code>
<code>databases/mariadb*-client</code> one of these ports provides <code>mysqldump</code>
<code>databases/mysql5*-client</code> one of these ports provides <code>mysqldump</code>
<code>openldap24-server</code> provides <code>slapcat</code>
<code>security/sudo</code> provides <code>sudo</code>
<code>sysutils/flock</code> probably a default on GNU/Linux, provides <code>flock</code> executable on FreeBSD
<code>textproc/jq</code> provides <code>jq</code>

Note that from the above list only <code>flock</code> and [jq](http://stedolan.github.io/jq/) are only mandatory requirements unless based on OmniBackup configuration other dependencies get pulled in. The best way to determine dependencies is to ignore the list of dependencies and first configure you OmniBackup instance. When your done with that, run OmniBackup manually for the first time. If it won't complain about any dependency then you are good to go. However, if it does, then you should resolve the dependencies one by one until you are good to go.


<br />
<a name="Installation"></a>

### Installation ###

Installing OmniBackup is really easy. It consists of two files: a huge script file, a little more than <code>100 KB</code> named <code>backup.sh</code> which looks for the second file at runtime named <code>config.json</code>. So, let's say I want to install OmniBackup inside <code>/usr/local/omnibackup</code> (I assume from now on you do everything as <code>root</code>):

    $ cd /usr/local/
    $ git clone https://gitlab.com/NuLL3rr0r/omnibackup.git
    $ cd omnibackup
    $ cp config.json.sample config.json
    $ chmod u+rx,go-r,a-w backup.sh
    $ chmod u+rw,go-rw,a-x config.json

All we did was cloning the code from [GitLab](https://gitlab.com/), copying over the sample configuration file as a template and assigning the right permissions for both the script and configuration file. I prefer to make this files <code>root</code> accessible only so no one else can read our configuration or modify it or even triggering the backup process.

You should avoid running the backup script in this step. As I mentioned this is just a sample file to get you up and running. You should only run it after the final configuration since it pickups possible dependencies from the configuration file and it may baffles you with the wrong dependencies errors. So, for now open-up the configuration file in your favorite editor and take a look.


<br />
<a name="ConfigTempDirectory"></a>

### Configuring Temporary Directory ###

The first option inside <code>config.json</code> file is <code>.temp_dir</code> which specifes the temporary or working directory for OmniBackup. <code>/var/tmp</code> seems to be a reasonable place. Feel free to adopt it according to your needs. But, if you are going to change it to a path other than <code>/var/tmp/</code> or <code>/tmp/</code> choose an empty one. Note that each time you run OmniBackup it creates a log file inside <code>/var/tmp/</code> e.g. <code>/var/tmp/backup.2015-07-31.58471.log</code>. You cannot change the path for the log files due to technical limitations. Keep in mind that OmniBackup never removes it log files due to their small footprints. They also may come handy when reports won't deliver to your email.

{% codeblock config.json lang:js %}
{
    "temp_dir" :  "/var/tmp",
}
{% endcodeblock %}


<br />
<a name="ConfigCompression"></a>

### Configuring Compression ###

There are three options for compression:

{% codeblock config.json lang:js %}
{
    "compression" :
    {
        "algorithm"            : "lzma2",
        "level"                : "6e",
        "preserve_permissions" : "yes"
    },
}
{% endcodeblock %}

<code>.compression.algorithm</code> accepts only four possible values: <code>lzma2</code>, <code>gzip</code> and <code>bzip2</code> which determines the compression algorithm, or, you can leave it empty for no compression. This affects the extension of the backup file which we call archive from now on. For <code>lzma2</code> it will be <code>.tar.xz</code>, for <code>gzip</code>, <code>.tar.gz</code>, for <code>bzip2</code>, <code>tar.bz2</code> and for no compression mode it will be simply <code>.tar</code>. Also, <code>lzma2</code>, <code>gizp</code> and <code>bzip2</code> values, pull in <code>xz</code>, <code>gizp</code> and <code>bizip2</code> binaries as dependency, respectively.

For <code>gizp</code> and <code>bzip2</code> algorithms, <code>.compression.level</code> option accepts values between <code>1</code> to <code>9</code>. For <code>lzma2</code> algorithm it accepts values between <code>1</code> to <code>9</code> and <code>1e</code> to <code>9e</code>. <code>e</code> stands for extreme and aggressive compression which demands more RAM and CPU cycles. In case you choose no compression mode, the <code>level</code> will be ignored.

<code>.compression.preserve_permissions</code> is self-explanatory, it preserve the archived files permissions inside the final archive file.


<br />
<a name="ConfigSecurity"></a>

### Configuring Security ###

Security module provides many features that you may not notice at the first sight:

{% codeblock config.json lang:js %}
{
    "security" :
    {
        "checksum_algorithm" :  "sha512",

        "encryption" :
        {
            "enable"                    :  "yes",
            "key_size"                  :  "256",
            "base64_encode"             :  "no",
            "passphrase"                :  "",
            "random_passphrase_pattern" :  "print",
            "random_passphrase_length"  :  128,
            "private_key"               :  "~/keys/private.pem"
        }
    },
}
{% endcodeblock %}

Please be wary, this module heavily relies on [OpenSSL](https://www.openssl.org/). So, some of the hash or encryption algorithms may not work in case you or your distribution built OpenSSL with those options excluded.

<code>.security.checksum_algorithm</code> provides various hash algorithm to verify the archive file integrity later on. <code>md4</code>, <code>md5</code>, <code>mdc2</code>, <code>ripemd160</code>, <code>sha</code>, <code>sha1</code>, <code>sha224</code>, <code>sha256</code>, <code>sha384</code>, <code>sha512</code> and <code>whirlpool</code> algorithms are all valid options and well supported. If encryption is disabled or you did not provide a private key, OmniBackup creates a checksum file with extension <code>.sum</code> which includes the archive checksum and uploads it along with your archive file. If encryption is enabled and you did provide a private key it uses the checksum file to sign the archive and instead of uploading <code>.sum</code> file, uploads the signature file with extension <code>.sign</code>, so that it can be verified using your public key at the destination. In either case OmniBackup includes the checksum in reports and send it through email to you.

<code>.security.encryption.enable</code> should either set to <code>yes</code> or <code>no</code>. If you set it to <code>no</code> the rest of the options will be ignored.

<code>.security.encryption.key_size</code> only accepts <code>128</code>, <code>192</code> and <code>256</code> which in turn enables AES-128, AES-192 and AES-256 encryption.

<code>.security.encryption.base64_encode</code> if you set it to <code>yes</code> encrypted archive file, signature file and the encrypted archive passphrase will be base64 encoded, otherwise they all be in binary format which saves up disk space and bandwidth.

<code>.security.encryption.passphrase</code> is the passphrase to encrypt or decrypt archive files. If you leave it blank it, OmniBackup generates a random password for each archive file. Otherwise, it uses the specified password for all archive files and ignore both <code>random_passphrase_pattern</code> and <code>random_passphrase_length</code>. If you decide to use a unique password for all backups make sure <code>config.json</code> is only readable by its owner. If set to blank, it pulls in <code>grep</code>, <code>head</code>, <code>strings</code> and <code>tr</code> as dependency.

<code>.security.encryption.random_passphrase_pattern</code> indicates the pattern to generate random passphrase for more info see [GNU](http://www.gnu.org/software/grep/manual/html_node/Character-Classes-and-Bracket-Expressions.html) and [BSD](https://www.freebsd.org/cgi/man.cgi?query=grep) implementation of grep:

* <code>alnum</code>: Alphanumeric characters: <code>alpha</code> and <code>digit</code>; in the <code>C</code> locale and ASCII character encoding, this is the same as <code>[0-9A-Za-z]</code>.
* <code>alpha</code>: Alphabetic characters: <code>lower</code> and <code>upper</code>; in the <code>C</code> locale and ASCII character encoding, this is the same as <code>[A-Za-z]</code>.
* <code>blank</code>: Blank characters: space and tab.
* <code>cntrl</code>: Control characters. In ASCII, these characters have octal codes <code>000</code> through <code>037</code>, and <code>177 (DEL)</code>. In other character sets, these are the equivalent characters, if any.
* <code>digit</code>: Digits: 0 1 2 3 4 5 6 7 8 9.
* <code>graph</code>: Graphical characters: <code>alnum</code> and <code>punct</code>.
* <code>lower</code>: Lower-case letters; in the <code>C</code> locale and ASCII character encoding, this is <code>a b c d e f g h i j k l m n o p q r s t u v w x y z</code>.
* <code>print</code>: Printable characters: <code>alnum</code>, <code>punct</code>, and space.
* <code>punct</code>: Punctuation characters; in the <code>C</code> locale and ASCII character encoding, this is <code>! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~</code>.
* <code>space</code>: Space characters: in the <code>C</code> locale, this is tab, newline, vertical tab, form feed, carriage return, and space.
* <code>upper</code>: Upper-case letters: in the <code>C</code> locale and ASCII character encoding, this is <code>A B C D E F G H I J K L M N O P Q R S T U V W X Y Z</code>.
* <code>xdigit</code>: Hexadecimal digits: <code>0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f</code>.

<code>.security.encryption.random_passphrase_length</code> a positive number bigger than <code>0</code> indicates the length of random passphrase.

<code>.security.encryption.private_key</code> is used to sign the encrypted archive file so anyone knows the file originated from you. Note it only accepts absolute path and relative paths starting from home folder (tilde <code>~</code>). Also, keep in mind that avoid space and exotic characters inside path. It's both sane and safe to only include A-Z, a-z and underscore in path because I cannot guarantee its safety.


<br />
<a name="ConfigReports"></a>

### Configuring Reports ###

Reports module is here to allow you become aware of all the details of the events that happened during the backup process through email:

{% codeblock config.json lang:js %}
{
    "reports" :
    {
        "mailboxes" :
        [
            {
                "email_address"      :  "backups.archive@babaei.net",
                "attach_passphrases" :  "yes"
            },
            {
                "email_address"      :  "backups.verify@babaei.net",
                "attach_passphrases" :  "no"
            }
        ],

        "subject" :
        {
            "success" :  "[{HOST_NAME} {DATE}] BACKUP REPORT / SUCCESS",
            "error"   :  "[{HOST_NAME} {DATE}] BACKUP REPORT / ERROR",
            "fatal"   :  "[{HOST_NAME} {DATE}] BACKUP REPORT / FATAL ERROR"
        },

        "support_info" :  "Have question or need technical assistance, please visit http://www.babaei.net/ or write an email to info [ at ] babaei.net."
    },
}
{% endcodeblock %}

<code>.reports.mailboxes</code> is a JSON array of email addresses and their settings who will receive the backup report when it's done, either successfully or failed.

<code>.reports.mailboxes.email_address</code> should be a valid email address.

<code>.reports.mailboxes.attach_passphrases</code> determines whether the archive passphrases should be attached to the reports for that specific email or not.

<code>.reports.subject</code> provides the ability to determine the report subject for different scenarios that might happen during the backup process, so by looking at your inbox you immediately realize what happened and take action if it's neccessary. <code>{HOST_NAME}</code> and <code>{DATE}</code> are special placeholder keywords. They will be replaceed at runtime by the host name OmniBackup backup running on or the date the backup jobs started, respectively.

<code>.reports.success</code> is email subject when backup process finished successfully.

<code>.reports.error</code> is email subject when at least one error happened during the backup process.

<code>.reports.fatal</code> is email subject when backup process faces a fatal error so it could not finish the jobs.

<code>.reports.support_info</code>

<br />
<a name="ConfigRemoteBackupServers"></a>

### Configuring Remote Backup Servers ###

{% codeblock config.json lang:js %}
{
    "remote" :
    {
        "keep_backup_locally" :  "partial",

        "servers" :
        [
            {
                "host"                :  "10.12.0.4",
                "port"                :  "22",
                "user"                :  "babaei",
                "dir"                 :  "~/backups/{HOST_NAME}",
                "backups_to_preserve" :  7,
                "public_key"          :  "~/keys/10.12.0.4-babaei.pem"
            },
            {
                "host"                :  "10.10.0.18",
                "port"                :  "8931",
                "user"                :  "babaei",
                "dir"                 :  "~/backups/{HOST_NAME}",
                "backups_to_preserve" :  31,
                "public_key"          :  "~/keys/10.10.0.18-babaei.pem"
            }
        ]
    },
}
{% endcodeblock %}


<br />
<a name="ConfigBackupTasks"></a>

### Configuring Backup Tasks ###

{% codeblock config.json lang:js %}
{
    "backup" :
    {
        "archive_name" :  "{DATE}_{HOST_NAME}_{TAG}",
    },
}
{% endcodeblock %}


<br />
<a name="ConfigBackupPriorityOrder"></a>

### Configuring Backup Priority and Order ###

{% codeblock config.json lang:js %}
{
    "backup" :
    {
        "priority_order" :
        [
            "openldap",
            "database",
            "filesystem",
            "misc"
        ],
    },
}
{% endcodeblock %}


<br />
<a name="ConfigOpenLdapBackups"></a>

### Configuring OpenLDAP Backups ###

{% codeblock config.json lang:js %}
{
    "backup" :
    {
        "openldap" :
        {
            "flags" :  "",
            "tag"   :  "openldap-babaei-net"
        },
    },
}
{% endcodeblock %}


<br />
<a name="ConfigDatabaseBackups"></a>

### Configuring Database Backups ###

{% codeblock config.json lang:js %}
{
    "backup" :
    {
        "database" :
        {
            "priority_order" :
            [
                "postgres",
                "mysql"
            ],
        },
    },
}
{% endcodeblock %}


<br />
<a name="ConfigPostgreSqlBackups"></a>

### Configuring PostgreSQL Database Backups ###

{% codeblock config.json lang:js %}
{
    "backup" :
    {
        "database" :
        {
            "postgres" :
            {
                "user" :  "pgsql",

                "databases" :
                [
                    {
                        "tag"     :  "postgres",
                        "name"    :  "*",
                        "comment" :  "All PostgreSQL databases"
                    },
                    {
                        "tag"     :  "postgres-gitlab",
                        "name"    :  "gitlab",
                        "comment" :  "GitLab database"
                    },
                    {
                        "tag"     :  "postgres-redmine",
                        "name"    :  "redmine",
                        "comment" :  "Redmine database"
                    },
                    {
                        "tag"     :  "postgres-agilo",
                        "name"    :  "agilo",
                        "comment" :  "Agilo for Trac database"
                    },
                    {
                        "tag"     :  "postgres-owncloud",
                        "name"    :  "owncloud",
                        "comment" :  "ownCloud database"
                    },
                    {
                        "tag"     :  "postgres-tracks",
                        "name"    :  "tracks",
                        "comment" :  "Get on Tracks database"
                    }
                ]
            },
        },
    },
}
{% endcodeblock %}


<br />
<a name="ConfigMariaDbMySqlBackups"></a>

### Configuring MariaDB and MySQL Databases Backups ###

{% codeblock config.json lang:js %}
{
    "backup" :
    {
        "database" :
        {
            "mysql" :
            {
                "user" :  "root",

                "databases" :
                [
                    {
                        "tag"     :  "mysql",
                        "name"    :  "*",
                        "comment" :  "All MySQL databases"
                    },
                    {
                        "tag"     :  "mysql-piwik",
                        "name"    :  "piwik",
                        "comment" :  "Piwik database"
                    },
                    {
                        "tag"     :  "mysql-osticket",
                        "name"    :  "osticket",
                        "comment" :  "Piwik database"
                    }
                ]
            }
        },
    },
}
{% endcodeblock %}


<br />
<a name="ConfigFilesystemBackups"></a>

### Configuring Filesystem Backups ###

{% codeblock config.json lang:js %}
{
    "backup" :
    {
        "filesystem" :
        [
            {
                "tag"             :  "www",
                "path"            :  "/usr/local/www/nginx",
                "follow_symlinks" :  "yes",
                "comment"         :  "Web server root directory"
            },
            {
                "tag"             :  "repos",
                "path"            :  "/usr/local/gitlab",
                "follow_symlinks" :  "yes",
                "comment"         :  "GitLab repositories"
            },
            {
                "tag"             :  "mail",
                "path"            :  "/usr/local/mail",
                "follow_symlinks" :  "yes",
                "comment"         :  "Mail server root directory"
            },
            {
                "tag"             :  "etc-system",
                "path"            :  "/etc",
                "follow_symlinks" :  "yes",
                "comment"         :  "Base system configurations"
            },
            {
                "tag"             :  "etc-ports",
                "path"            :  "/usr/local/etc",
                "follow_symlinks" :  "yes",
                "comment"         :  "Installed ports configurations"
            },
            {
                "tag"             :  "loader-conf",
                "path"            :  "/boot/loader.conf",
                "follow_symlinks" :  "yes",
                "comment"         :  "System bootstrap configuration information"
            },
            {
                "tag"             :  "boot-splash",
                "path"            :  "/boot/splash.pcx",
                "follow_symlinks" :  "yes",
                "comment"         :  "Boot-time splash screen"
            },
            {
                "tag"             :  "slim-fbsd-theme",
                "path"            :  "/usr/local/share/slim/themes/fbsd",
                "follow_symlinks" :  "yes",
                "comment"         :  "FreeBSD SLiM theme"
            }
        ],
    },
}
{% endcodeblock %}

<br />
<a name="ConfigOtherBackups"></a>

### Configuring Other Backups ###

{% codeblock config.json lang:js %}
{
    "backup" :
    {
        "misc" :
        [
            {
                "tag"                   :  "cloudflare-ip-ranges",
                "command"               :  "/usr/local/www/nginx/cron/cloudflare-ip-ranges-updater.sh",
                "args"                  :  "ipv4 ipv6",
                "path"                  :  "/usr/local/www/nginx/include/cloudflare",
                "follow_symlinks"       :  "yes",
                "remove_path_when_done" :  "no",
                "comment"               :  "CloudFlare IP database for nginx RealIP module"
            }
        ]
    },
}
{% endcodeblock %}


<br />
<a name="Config3rdPartyCommandsStatusCode"></a>

### 3rd-party Commands Status Codes ###

{% codeblock config.json lang:js %}
{
    "command" :
    {
        "basename" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "bzip2" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "caller" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "cat" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "cd" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "cut" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "date" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "du" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "dirname" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "echo" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "expr" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "flock" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "grep" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "gzip" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "head" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "hostname" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "jq" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_1"   :  "The last output value was either false or null.",
                "rc_2"   :  "Usage problem or system error.",
                "rc_3"   :  "Compile error,.",
                "rc_4"   :  "Parse error.",
                "rc_any" :  "The operation failed."
            }
        },

        "logger" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "mail" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "mkdir" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "mysqldump" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "openssl" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "pg_dump" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "pg_dumpall" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "printf" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "readlink" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "rm" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "scp" :
        {
            "return_code" :
            {
                "rc_0"   :  "Operation was successful.",
                "rc_1"   :  "General error in file copy.",
                "rc_2"   :  "Destination is not directory, but it should be.",
                "rc_3"   :  "Maximum symlink level exceeded.",
                "rc_4"   :  "Connecting to host failed.",
                "rc_5"   :  "Connection broken.",
                "rc_6"   :  "File does not exist.",
                "rc_7"   :  "No permission to access file.",
                "rc_8"   :  "General error in sftp protocol.",
                "rc_9"   :  "File transfer protocol mismatch.",
                "rc_10"  :  "No file matches a given criteria.",
                "rc_65"  :  "Host not allowed to connect.",
                "rc_66"  :  "General error in ssh protocol.",
                "rc_67"  :  "Key exchange failed.",
                "rc_68"  :  "Reserved.",
                "rc_69"  :  "MAC error.",
                "rc_70"  :  "Compression error.",
                "rc_71"  :  "Service not available.",
                "rc_72"  :  "Protocol version not supported.",
                "rc_73"  :  "Host key not verifiable.",
                "rc_74"  :  "Connection failed.",
                "rc_75"  :  "Disconnected by application.",
                "rc_76"  :  "Too many connections.",
                "rc_77"  :  "Authentication cancelled by user.",
                "rc_78"  :  "No more authentication methods available.",
                "rc_79"  :  "Invalid user name.",
                "rc_any" :  "Unknown scp error."
            }
        },

        "slapcat" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "ssh" :
        {
            "return_code" :
            {
                "rc_0"   :  "Operation was successful.",
                "rc_1"   :  "Generic error.",
                "rc_2"   :  "Connection failed.",
                "rc_10"  :  "No file matches a given criteria.",
                "rc_65"  :  "Host not allowed to connect.",
                "rc_66"  :  "General error in ssh protocol.",
                "rc_67"  :  "Key exchange failed.",
                "rc_68"  :  "Reserved.",
                "rc_69"  :  "MAC error.",
                "rc_70"  :  "Compression error.",
                "rc_71"  :  "Service not available.",
                "rc_72"  :  "Protocol version not supported.",
                "rc_73"  :  "Host key not verifiable.",
                "rc_74"  :  "Connection failed.",
                "rc_75"  :  "Disconnected by application.",
                "rc_76"  :  "Too many connections.",
                "rc_77"  :  "Authentication cancelled by user.",
                "rc_78"  :  "No more authentication methods available.",
                "rc_79"  :  "Invalid user name.",
                "rc_255" :  "Generic ssh error.",
                "rc_any" :  "Unknown ssh error."
            }
        },

        "strings" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "sudo" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "tar" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "tr" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        },

        "xz" :
        {
            "return_code" :
            {
                "rc_0"   :  "The operation completed successfully.",
                "rc_any" :  "The operation failed."
            }
        }
    }
}
{% endcodeblock %}



<br />
<a name="FirstRun"></a>

### First Run ###


<br />
<a name="Crontab"></a>

### Crontab ###

It is recommended to [learn the fundamentals of configuring cron](/blog/2015/06/11/the-proper-way-of-adding-a-cron-job/) if you are not familiar with the topic. Anyway to schedule a backup task as user <code>root</code>:

    $ crontab -e -u root

Then add the backup cron job and make sure the PATH variable is peresent with the following values:

{% codeblock config.json lang:js %}
SHELL=/bin/sh
PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin
MAILTO=""

# Order of crontab fields
# minute    hour    mday    month   wday    command

# OmniBackup
# at 01:00am UTC
00      01      *       *       *       /usr/local/omnibackup/backup.sh
{% endcodeblock %}

To see whether the cron job was added successfully or not, you can issue the following command:

    $ crontab -l -u root

In the above example I scheduled the backup task to run at <code>01:00 AM</code> and since the server timezone is UTC it will run at <code>01:00 AM UTC</code> each night. To verify if the backup task runs properly, we can run the script with a limited set of environment variables:

    $ env -i SHELL=/bin/sh PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin HOME=/root LOGNAME=Charlie /usr/local/omnibackup/backup.sh


<br />
<a name="SourceCode"></a>

### Source Code ###

[Check out source code on GitLab](https://gitlab.com/NuLL3rr0r/omnibackup/)

[Check out source code on GitHub](https://github.com/NuLL3rr0r/omnibackup/)


