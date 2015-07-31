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

Today is _[System Administrator Appreciation Day](http://sysadminday.com/)_. It is celebrated on the last _Friday_ in _July_ and it has been celebrated since _July 28, 2000_. But, system administrators know not all days are like today. They face many hard times and struggles during their careers and the worse of them all is either a [security breech](/blog/2015/07/30/freebsd-block-brute-force-attacks-using-sshguard-and-ipfw-firewall/) or data loss.

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

**_Disclaimer_**: Please be wary of the fact that this script has 3.3K lines of Bash code and devoured hell of a time from me to write and debug. You should also consider that this is my first heavy Bash experiment and I may not write quality code in the language since I'm a newcomer to Bash. I do not claim this OmniBackup is production ready, that's why I did version the first release at <code>0.1.0</code>. Also note that OmniBackup heavily relies on 3rd-party software which increase the chance for fatal bugs, therefore losing data. So, I provide OmniBackup without any warranties, guarantees or conditions, of any kind and I accept no liability or responsibility any misuse or damages. Please use it at your own risk and remember you're solely responsible for any resulting damage or data loss.

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
* [Configuration](#Configuration)  
* [Configuring Temporary Directory](#ConfigTempDirectory)  
* [Configuring Compression](#ConfigCompression)  
* [Configuring Security](#ConfigSecurity)  
* [Configuring Reports](#ConfigReports)  
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

There are different kind of messages in OmniBackup:

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

Note that from the above list only <code>flock</code> and <code>jq</code> are mandatory requirements unless based on OmniBackup configuration other dependencies get pulled in. The best way to determine dependencies is to ignore the list of dependencies and first configure you OmniBackup instance. When your done with that, run OmniBackup manually for the first time. If it won't complain about any dependency then you are good to go. However, if it does, then you should resolve the dependencies one by one until you are good to go.




