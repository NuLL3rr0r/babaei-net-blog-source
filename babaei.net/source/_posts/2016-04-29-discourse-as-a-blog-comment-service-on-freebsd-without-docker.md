---
title: "Discourse as a Blog Comment Service on FreeBSD without Docker"
date: 2016-04-29 06:49:31
tags:
  - Docker
  - FreeBSD
  - GNU
  - Hexo
  - Linux
  - Ruby
  - Ruby on Rails
  - Unix
---

[{% img post-image /blog/2016/04/29/discourse-as-a-blog-comment-service-on-freebsd-without-docker/discourse-logo.png 1000 293 "'Discourse Logo'" "'Discourse Logo'" %}](/blog/2016/04/29/discourse-as-a-blog-comment-service-on-freebsd-without-docker/discourse-logo.png)
<span class="post-image-title">Figure 1. Discourse Logo</span>

Well, when it comes to blog comment hosting services for static blogs, you will have a plethora of options such as [SolidOpinion](http://solidopinion.com/), [Disqus](https://disqus.com/), [Livefyre](http://web.livefyre.com/), Google+ or Facebook comments, and many more. Unfortunately, such services has never been an option for me and I resisted them like forever. Yes, I've got one million reasons to believe and do so which demands another post of its own. So, I'll avoid that argument for now.

This left me with two choices:

* Operate my blogs without the comment section as I did for years
* Running an open source self-host blog comment system such as [HashOver](https://github.com/jacobwb/hashover), [Isso](https://github.com/posativ/isso), [Juvia](https://github.com/phusion/juvia) and [talkatv](https://github.com/talkatv/talkatv)

Since people asked me for a way to discuss their feedback on the website, this made the former choice a no go, anymore. So, in a search for the promised commenting system, I spent hours installing and trying every single FLOSS commenting system on GitHub. And everyone of them has had a big flaw that I could not tolerate. Finally, I came to the conclusion that I'm out of luck with that. Of course, I always had the option to write my own commenting system according to my own needs. As, I did with [my own blog subscription system](https://github.com/NuLL3rr0r/blog-subscription-service/). But, due to the lack of time that was not an option either.

It happens that I randomly visit [Coding Horror by Jeff Atwood](http://blog.codinghorror.com/) the co-founder of [Stack Overflow](https://stackoverflow.com/) and [Stack Exchange Network](http://stackexchange.com/). I've always read the comments on Coding Horror but never had an urge to write a comment their. Since I've been desperately looking for a commenting system, this time the different look of its comment system catched my attention. Bingo! He wrote an open source discussion platform software named [Discourse](http://www.discourse.org/). Not necessarily a blog comment system, but [could be used as one](https://meta.discourse.org/t/embedding-discourse-comments-via-javascript/31963). It even supports [the Farsi language and RTL out of the box](https://meta.discourse.org/t/rtl-support/1784/82) which allows me to use it on [my Farsi blog](http://fa.babaei.net), too. In addition to that it supports multi-site which means I have to only run one instance for all my blogs. Just perfect!

Despite many nice feature it provides, it has a few rough edges, too. I was able to conquer some and some couldn't, yet. But it did not stop me from integrating it into my [Hexo](https://hexo.io/)-based blogs after two weeks of testing it. So, there it is, from now on both [this blog](http://www.babaei.net/) and [my Farsi blog](http://fa.babaei.net/) are discussion aware :).

OK, the main issue that many people face when they want to install Discourse in a platform other than GNU/Linux, is they get hit in the face by the reading this line in the official documentation:

{% blockquote How Do I Install Discourse? https://github.com/discourse/discourse/blob/master/docs/INSTALL.md %}
Why do you only officially support Docker?

Hosting Rails applications is complicated. Even if you already have Postgres, Redis and Ruby installed on your server, you still need to worry about running and monitoring your Sidekiq and Rails processes. Additionally, our Docker install comes bundled with a web-based GUI that makes upgrading to new versions of Discourse as easy as clicking a button.
{% endblockquote %}

Yes, I know Ruby and Rails are crap and deploying Ruby on Rails apps are pain in the Butt. Do not worry! This was [the first struggle with Discourse that I had](https://forums.freebsd.org/threads/55965/) since this blog runs on FreeBSD. And, [FreeBSD support for Docker](https://wiki.freebsd.org/Docker) is experimental, yet. Fortunately, I used to deploy [GitLab](https://github.com/gitlabhq/gitlabhq) instances on FreeBSD for three years which was also RoR before I migrated to [Gogs](https://github.com/gogits/gogs) which kicks butt, anyway! That made it easy to figure out a simple way to deploy Discourse without Docker on FreeBSD.

<!-- more -->

### Dependencies ###

Assuming you have <code>ports-mgmt/pkg</code> (a.k.a pkgng) installed and initialized, we have to check for and install the missing Discourse dependencies:

    $ pkg info | grep bundler
    rubygem-bundler-1.11.2         Tool that manages gem dependencies for ruby applications
    
    $ pkg info | grep gcc
    gcc-4.8.5_2                    GNU Compiler Collection 4.8
    
    $ pkg info | grep gems
    ruby22-gems-2.6.2              Package management framework for the Ruby language
    
    $ pkg info | grep gifsicle
    gifsicle-1.88                  Manipulates GIF images and animations
    
    $ pkg info | grep git
    git-2.8.1                      Distributed source code management tool
    
    $ pkg info | grep gmake
    gmake-4.1_2                    GNU version of 'make' utility
    
    $ pkg info | grep ImageMagick
    ImageMagick-nox11-6.9.3.8_1,1  Image processing tools
    
    $ pkg info | grep jpeg-turbo
    jpeg-turbo-1.4.2               SIMD-accelerated JPEG codec which replaces libjpeg
    
    $ pkg info | grep libxml2
    libxml2-2.9.3                  XML parser library for GNOME
    
    $ pkg info | grep postgres
    postgresql94-server-9.4.7      The most advanced open-source database available anywhere

    $ pkg info | grep postgres
    postgresql94-contrib-9.4.7     The contrib utilities from the PostgreSQL distribution
    
    $ pkg info | grep redis
    redis-3.0.7                    Persistent key-value database with built-in net interface
    
    $ pkg info | grep ruby
    ruby-2.2.4,1                   Object-oriented interpreted scripting language

    $ pkg info | grep sudo
    sudo-1.8.16                    Allow others to run commands as root

In my case the only missing dependencies were <code>graphics/ImageMagick</code> and <code>graphics/gifsicle</code>. So if you want to install from source using Ports:

    $ cd /usr/ports/graphics/ImageMagick-nox11/
    $ make config-recursive
    $ make install clean
    
    $ cd /usr/ports/graphics/gifsicle/
    $ make config-recursive
    $ make install clean

Or, alternatively install the binaries using pkgng:

    $ pkg install graphics/ImageMagick-nox11 graphics/gifsicle

Note that I choose graphics/ImageMagick-nox11 over graphics/ImageMagick since it pulls in less dependency.


### Database ###

OK, after installing the required dependencies, it's time to initialize the database by creating a user name and a password. In addition to that we have to enable the required PostgreSQL extensions.

By default, Discourse chooses <code>discourse</code> for both database name and user name. I'll choose <code>discourse</code> user name and <code>discourse_production</code> for database name. Let's assume that I want [discuss.babaei.net](http://discuss.babaei.net/) and [discuss.fa.babaei.net](http://discuss.fa.babaei.net/) share the same Discourse instance.

If you are planing to run only one website / blog on Discourse:

    $ sudo -u pgsql psql -d template1
    template1=# CREATE USER discourse CREATEDB;
    template1=# CREATE DATABASE discourse_production WITH ENCODING='UTF8' OWNER discourse;
    template1=# \l
    template1=# \c discourse_production
    discourse_production=# CREATE EXTENSION hstore;
    discourse_production=# CREATE EXTENSION pg_trgm;

If you plan for a multi-site install, <s>in addition to the above commands</s>:

    discourse_production=# CREATE DATABASE discourse_babaei_net_production WITH ENCODING='UTF8' OWNER discourse;
    discourse_production=# CREATE DATABASE discourse_fa_babaei_net_production WITH ENCODING='UTF8' OWNER discourse;
    discourse_production=# \l
    discourse_production=# \c discourse_babaei_net_production
    discourse_babaei_net_production=# CREATE EXTENSION hstore;
    discourse_babaei_net_production=# CREATE EXTENSION pg_trgm;
    discourse_babaei_net_production=# \c discourse_fa_babaei_net_production
    discourse_fa_babaei_net_production=# CREATE EXTENSION hstore;
    discourse_fa_babaei_net_production=# CREATE EXTENSION pg_trgm;

Finally exit PostgreSQL command line by issuing: <code>\q</code>.

One more thing: it's possible to protect the user login with a password. In that case, instead of:

    template1=# CREATE USER discourse CREATEDB;

Create the user using this command:

    template1=# CREATE ROLE discourse LOGIN ENCRYPTED PASSWORD '${SECRET_PASSWORD}' NOINHERIT VALID UNTIL 'infinity';

Obviously instead of <code>${SECRET_PASSWORD}</code> you must put your own password. Since PostgreSQL by default do not listen for external connections and only accepts local requests, you may find it unnecessary to password-protect the user login unless you are running Discourse and PostgreSQL on different machines.

You can check whether your PostgreSQL instance refuses external connections or not by taking a look at <code>/usr/local/pgsql/data/pg_hba.conf</code>:

    # TYPE  DATABASE        USER            ADDRESS                 METHOD

    # "local" is for Unix domain socket connections only
    local   all             all                                     trust
    # IPv4 local connections:
    host    all             all             127.0.0.1/32            trust
    # IPv6 local connections:
    host    all             all             ::1/128                 trust
    # Allow replication connections from localhost, by a user with the
    # replication privilege.
    #local   replication     pgsql                                trust
    #host    replication     pgsql        127.0.0.1/32            trust
    #host    replication     pgsql        ::1/128                 trust

The above default settings allows local connectons only.


### System User and Group ###

Now that we've initialized the database, we have to create the Discourse system user name and group. Note that the user name must be the same as the user name you chose at the previous step. We chose <code>discourse</code> user name at the time of database creation. We'll also go with <code>/home/discourse</code> as Discourse home directory. So:

    $ pw addgroup discourse
    $ pw adduser discourse -g discourse -m -d /home/discourse -c "Discourse"
    $ pw usermod discourse -G redis

So, We did create the user and its group. Moreover, we add the user to <code>redis</code> group.


### Source Code ###

Now that we have the Discourse user added to the system:

    $ cd /home/discourse/
    $ sudo -u discourse -H git clone https://github.com/discourse/discourse.git

After cloning Discourse source code we have to find out the latest stable tag by issuing:
    
    $ cd /home/discourse/discourse/
    $ sudo -u discourse -H git tag -l

The output is something like this:

    latest-release
    v0.8.0
    v0.8.1
    v0.8.2
    v0.8.3
    v0.8.4
    v0.8.5
    v0.8.6
    v0.8.7
    v0.8.8
    v0.8.9
    v0.9.0
    v0.9.1
    v0.9.2
    v0.9.2.5
    v0.9.2.6
    v0.9.3
    v0.9.3.5
    v0.9.4
    v0.9.5
    v0.9.5.1
    v0.9.5.2
    v0.9.6
    v0.9.6.1
    v0.9.6.2
    v0.9.6.3
    v0.9.6.4
    v0.9.7
    v0.9.7.1
    v0.9.7.2
    v0.9.7.3
    v0.9.7.4
    v0.9.7.5
    v0.9.7.6
    v0.9.7.7
    v0.9.7.8
    v0.9.7.9
    v0.9.8
    v0.9.8.1
    v0.9.8.10
    v0.9.8.11
    v0.9.8.2
    v0.9.8.3
    v0.9.8.4
    v0.9.8.5
    v0.9.8.6
    v0.9.8.7
    v0.9.8.8
    v0.9.8.9
    v0.9.9
    v0.9.9.1
    v0.9.9.10
    v0.9.9.11
    v0.9.9.12
    v0.9.9.13
    v0.9.9.14
    v0.9.9.15
    v0.9.9.16
    v0.9.9.17
    v0.9.9.18
    v0.9.9.2
    v0.9.9.3
    v0.9.9.4
    v0.9.9.5
    v0.9.9.6
    v0.9.9.7
    v0.9.9.8
    v0.9.9.9
    v1.0.0
    v1.0.1
    v1.0.2
    v1.0.3
    v1.0.4
    v1.1.0
    v1.1.0.beta1
    v1.1.0.beta2
    v1.1.0.beta3
    v1.1.0.beta4
    v1.1.0.beta5
    v1.1.0.beta6
    v1.1.0.beta6b
    v1.1.0.beta7
    v1.1.0.beta8
    v1.1.1
    v1.1.2
    v1.1.3
    v1.2.0
    v1.2.0.beta1
    v1.2.0.beta2
    v1.2.0.beta3
    v1.2.0.beta4
    v1.2.0.beta5
    v1.2.0.beta6
    v1.2.0.beta7
    v1.2.0.beta8
    v1.2.0.beta9
    v1.2.1
    v1.2.2
    v1.2.3
    v1.2.4
    v1.3.0
    v1.3.0.beta1
    v1.3.0.beta10
    v1.3.0.beta11
    v1.3.0.beta2
    v1.3.0.beta3
    v1.3.0.beta4
    v1.3.0.beta5
    v1.3.0.beta6
    v1.3.0.beta7
    v1.3.0.beta8
    v1.3.0.beta9
    v1.3.1
    v1.3.2
    v1.3.3
    v1.3.4
    v1.3.5
    v1.4.0
    v1.4.0.beta1
    v1.4.0.beta10
    v1.4.0.beta11
    v1.4.0.beta12
    v1.4.0.beta2
    v1.4.0.beta3
    v1.4.0.beta4
    v1.4.0.beta5
    v1.4.0.beta6
    v1.4.0.beta7
    v1.4.0.beta8
    v1.4.0.beta9
    v1.4.1
    v1.4.2
    v1.4.3
    v1.4.4
    v1.4.5
    v1.4.6
    v1.4.7
    v1.5.0
    v1.5.0.beta1
    v1.5.0.beta10
    v1.5.0.beta11
    v1.5.0.beta12
    v1.5.0.beta13
    v1.5.0.beta13b
    v1.5.0.beta14
    v1.5.0.beta2
    v1.5.0.beta3
    v1.5.0.beta4
    v1.5.0.beta5
    v1.5.0.beta6
    v1.5.0.beta7
    v1.5.0.beta8
    v1.5.0.beta9
    v1.5.1
    v1.6.0.beta1
    v1.6.0.beta2

In the above output, the latest stable release is <code>v1.5.1</code> while <code>latest-release</code> tag is the latest beta, stable or whatever it is. So, I'll checkout <code>v1.5.1</code> tag by:

    $ sudo -u discourse -H git checkout tags/v1.5.1


### Configuration Files ###

Most RoR applications have a section named <code>production</code> in <code>&lt;project-root&gt;/config/database.yml</code> file.

You'll only find the following comments inside <code>config/database.yml</code> for Discourse:

    # You may be surprised production is not here, it is sourced from application.rb using a monkey patch
    # This is done for 2 reasons
    #
    # 1. we need to support blank settings correctly and rendering nothing in yaml/erb is a PITA
    # 2. why go from object -> yaml -> object, pointless

Discourse is a bit different. It has some defaults values which you will be able to override. The default configuration resides inside <code>config/discourse_defaults.conf</code>:

    #
    # DO NOT EDIT THIS FILE
    # If you need to make changes create a file called discourse.conf in this directory with your changes
    # On import this file will be imported using ERB
    #

    # Discourse supports multiple mechanisms for production config.
    #
    # 1. You can do nothing and get these defaults (not recommended, you should at least set hostname)
    # 2. You can copy this file to config/discourse.conf and amend with your settings
    # 3. You can pass in config from your environment, all the settings below are available.
    #    Append DISCOURSE_ and upper case the setting in ENV. For example:
    #    to pass in db_timeout of 200 you would use DISCOURSE_DB_TIMEOUT=200

    # All settings apply to production only

    # connection pool size, sidekiq is set to 5, allowing an extra 3 for bg threads
    db_pool = 8

    # database timeout in milliseconds
    db_timeout = 5000

    # socket file used to access db
    db_socket =

    # host address for db server
    # This is set to blank so it tries to use sockets first
    db_host =

    # port running db server, no need to set it
    db_port =

    # database name running discourse
    db_name = discourse

    # username accessing database
    db_username = discourse

    # password used to access the db
    db_password =

    # Disallow prepared statements
    # see: https://github.com/rails/rails/issues/21992
    db_prepared_statements = false

    # host address for db replica server
    db_replica_host =

    # port running replica db server, defaults to 5432 if not set
    db_replica_port =

    # hostname running the forum
    hostname = "www.example.com"

    # backup hostname mainly for cdn use
    backup_hostname =

    # address of smtp server used to send emails
    smtp_address =

    # port of smtp server used to send emails
    smtp_port = 25

    # domain passed to smtp server
    smtp_domain =

    # username for smtp server
    smtp_user_name =

    # password for smtp server
    smtp_password =

    # smtp authentication mechanism
    smtp_authentication = plain

    # enable TLS encryption for smtp connections
    smtp_enable_start_tls = true

    # mode for verifying smtp server certificates
    # to disable, set to 'none'
    smtp_openssl_verify_mode =

    # load MiniProfiler in production, to be used by developers
    load_mini_profiler = true

    # recommended, cdn used to access assets
    cdn_url =

    # comma delimited list of emails that have developer level access
    developer_emails =

    # redis server address
    redis_host = localhost

    # redis server port
    redis_port = 6379

    # redis slave server address
    redis_slave_host =

    # redis slave server port
    redis_slave_port = 6379

    # redis database
    redis_db = 0

    # redis password
    redis_password =

    # redis sentinels eg
    # redis_sentinels = 10.0.0.1:26381,10.0.0.2:26381
    redis_sentinels =

    # enable Cross-origin Resource Sharing (CORS) directly at the application level
    enable_cors = false
    cors_origin = ''

    # enable if you really need to serve assets in prd
    serve_static_assets = false

    # number of sidekiq workers (launched via unicorn master)
    sidekiq_workers = 5

    # adjust stylesheets to rtl (requires "rtlit" gem)
    rtl_css = false

    # notify admin when a new version of discourse is released
    # this is global so it is easier to set in multisites
    # TODO allow for global overrides
    new_version_emails = true

    # connection reaping helps keep connection counts down, postgres
    # will not work properly with huge numbers of open connections
    # reap connections from pool that are older than 30 seconds
    connection_reaper_age = 30
    # run reap check every 30 seconds
    connection_reaper_interval = 30
    # also reap any connections older than this
    connection_reaper_max_age = 600

    # set to relative URL (for subdirectory hosting)
    # IMPORTANT: path must not include a trailing /
    # EG: /forum
    relative_url_root =

    # increasing this number will increase redis memory use
    # this ensures backlog (ability of channels to catch up are capped)
    # message bus default cap is 1000, we are winding it down to 100
    message_bus_max_backlog_size = 100

As the first line in that file suggests you must avoid touching this file. Instead create an empty file inside the same directory at <code>config/discourse.conf</code> which is <code>/home/discourse/discourse/config/discourse.conf</code> in our case and put the desired configuration there:

    # Database
    db_pool = 12
    db_name = discourse_production
    db_username = discourse
    #db_password =   # Only if the PostgreSQL user 'discourse' is password-protected

    # Hostname
    hostname = "babaei.net"

    # SMTP
    smtp_address = "127.0.0.1"
    smtp_port = 587
    smtp_user_name = "mailer@babaei.net"
    smtp_password = "${MAILER_SECRET_PASSWORD}"
    smtp_authentication = plain
    smtp_enable_start_tls = true

    # Admin Email
    developer_emails = admin@babaei.net

    # Sidekiq
    sidekiq_workers = 8

    # Update Notification
    new_version_emails = true

Note that some of the above settings are imaginary and is provided as an example. So, they might not work for you and you should adjust them according to your environment, or do not override the default ones at all.

If you are running a multi-site setup you have to create another file named <code>config/multisite.yml</code>. First take a look at <code>config/multisite.yml.production-sample</code> to get an idea of what its contents look like:

    mlp:
      adapter: postgresql
      database: discourse_mlp
      username: discourse_mlp
      password: applejack
      host: dbhost
      pool: 5
      timeout: 5000
      db_id: 1      # ensure db_id is unique for each site
      ### If you change this setting you will need to
      ###   - restart sidekiq if you change this setting
      ###   - rebake all to posts using: `RAILS_ENV=production bundle exec rake posts:rebake`
      host_names:
        - discourse.equestria.com
        - discourse.equestria.internal

    drwho:
      adapter: postgresql
      database: discourse_who
      username: discourse_who
      password: "Up the time stream without a TARDIS"
      host: dbhost
      pool: 5
      timeout: 5000
      db_id:        # ensure db_id is unique for each site
      ### If you change this setting you will need to
      ###   - restart sidekiq if you change this setting
      ###   - rebake all to posts using: `RAILS_ENV=production bundle exec rake posts:rebake`
      host_names:
        - discuss.tardis.gallifrey

So for our multi-site example I'll create the <code>/home/discourse/discourse/config/multisite.yml</code> with the following content:

    babaei_net_production:
      adapter: postgresql
      database: discourse_babaei_net_production
      username: discourse               # if using username/password auth
      # password: ${SECRET_PASSWORD}    # if using username/password auth
      # host: dbhost                    # if not localhost
      pool: 12
      timeout: 5000
      db_id: 1	# ensure db_id is unique for each site
      ### If you change this setting you will need to
      ###   - restart sidekiq if you change this setting
      ###   - rebake all to posts using: `sudo -u discourse -H RAILS_ENV=production bundle exec rake posts:rebake`
      host_names:
        - discuss.babaei.net

    fa_babaei_net_production:
      adapter: postgresql
      database: discourse_fa_babaei_net_production
      username: discourse               # if using username/password auth
      # password: ${SECRET_PASSWORD}    # if using username/password auth
      # host: dbhost                    # if not localhost
      pool: 12
      timeout: 5000
      db_id: 2	# ensure db_id is unique for each site
      ### If you change this setting you will need to
      ###   - restart sidekiq if you change this setting
      ###   - rebake all to posts using: `sudo -u discourse -H RAILS_ENV=production bundle exec rake posts:rebake`
      host_names:
        - discuss.fa.babaei.net


### Install Gems ###

    $ cd /home/discourse/discourse/
    $ sudo -u discourse -H bundle install --deployment --without test --without development

Grab a cup of coffee! This may take a while.


### Database Migration ###

No matter if this is the first time you install Discourse or you are upgrading, this is a necessary part of the process.

For single-site installations:

    $ cd /home/discourse/discourse/
    $ sudo -u discourse -H RAILS_ENV=production bundle exec rake db:migrate

For multi-site installations:

    $ cd /home/discourse/discourse/
    $ sudo -u discourse -H RAILS_ENV='production' bundle exec rake multisite:migrate


### Precompile Assets ###

    $ cd /home/discourse/discourse/
    $ sudo -u discourse -H RAILS_ENV=production bundle exec rake assets:precompile

This one should take some time to complete.


### Startup Script ###

Congratulations! If you made it so far you've probably setup Discourse successfully. But, before we run the Discourse application server let's write a small script to run it properly in a simple way.

First, let's create the required directories, and set the current permissions:

    $ sudo -u discourse -H mkdir -p /home/discourse/cron/
    $ sudo -u discourse -H mkdir -p /home/discourse/log/
    $ chmod -R g-rxw,o-rxw /home/discourse/cron
    $ chmod -R g-rxw,o-rxw /home/discourse/log
    $ chown -R www:www /home/discourse/log

Then, to write the script in your default editor (of course you can choose another editor by replacing $EDITOR environment variable in the following command, directly with your preferred editor executable's name):

    $ sudo -u discourse -H $EDITOR /home/discourse/cron/server.sh

Now copy paste the following and [be wary not to break the lines inside your editor](/blog/2013/02/17/nano-do-not-wrap-text/):

    #!/bin/sh

    cd /home/discourse/discourse/
    sudo -u discourse -H nohup bundle exec sidekiq -e production > /home/discourse/discourse/log/sidekiq.log 2>&1&
    sudo -u discourse -H RAILS_ENV=production RUBY_GC_MALLOC_LIMIT=90000000 nohup bundle exec thin start -s8 --socket /home/discourse/discourse/tmp/sockets/thin.sock > /home/discourse/discourse/log/thin.log 2>&1&

I chose to go with [Thin](http://code.macournoyer.com/thin/) and Unix domain sockets. That <code>-s8</code> argument creates eight Unix socket domain connections. So, change that according to your needs.

Alternatively it's possible to use TCP connections instead of Unix domain sockets (consider that Unix domain sockets can achieve better throughput than the TCP/IP loopback). To run Thin server and listen for connections on port <code>11011</code>, replace the last line of the script with:

    sudo -u discourse -H RAILS_ENV=production RUBY_GC_MALLOC_LIMIT=90000000 bundle exec thin start -p 11011 > /home/discourse/discourse/log/thin.log 2>&1&

To serve the application on default Rails server instead of Thin (Definitely a bad decision since it's slower), replace the last line of the script with:

    sudo -u discourse -H RAILS_ENV='production' RUBY_GC_MALLOC_LIMIT=90000000 bundle exec rails server /home/discourse/discourse/log/rails_server.log

By the way, you can read about [what's the big deal about that bloody RUBY_GC_MALLOC_LIMIT=90000000 here](https://meta.discourse.org/t/tuning-ruby-and-rails-for-discourse/4126).

Before running the script, set it executable for all users:

    $ chmod a+x /home/discourse/cron/server.sh

And then run the script if you wish:

    $ /home/discourse/cron/server.sh

To check if your Sidekiq instance and Thin server started successfully or not:

    $ ps auxw | grep ruby
    discourse    2573   0.0 12.9 1163352 178056  -  S    Mon01AM  128:25.44 ruby22: sidekiq 4.0.2 discourse [0 of 25 busy] (ruby22)
    discourse    2576   0.0 12.9  987464 177624  -  I    Mon01AM    6:58.57 ruby22: thin server (/home/discourse/discourse/tmp/sockets/thin.0.sock) (ruby22)
    discourse    2579   0.0 12.6  966856 187356  -  I    Mon01AM    5:32.62 ruby22: thin server (/home/discourse/discourse/tmp/sockets/thin.1.sock) (ruby22)
    discourse    2584   0.0 11.8  986264 182331  -  I    Mon01AM    6:38.12 ruby22: thin server (/home/discourse/discourse/tmp/sockets/thin.2.sock) (ruby22)
    discourse    2585   0.0 13.1  997361 177239  -  I    Mon01AM    5:59.31 ruby22: thin server (/home/discourse/discourse/tmp/sockets/thin.3.sock) (ruby22)
    discourse    2587   0.0 13.6  983232 183451  -  I    Mon01AM    5:49.12 ruby22: thin server (/home/discourse/discourse/tmp/sockets/thin.4.sock) (ruby22)
    discourse    2589   0.0 13.6  977334 182345  -  I    Mon01AM    5:17.11 ruby22: thin server (/home/discourse/discourse/tmp/sockets/thin.5.sock) (ruby22)
    discourse    2590   0.0 12.9  983232 193454  -  I    Mon01AM    6:33.88 ruby22: thin server (/home/discourse/discourse/tmp/sockets/thin.6.sock) (ruby22)
    discourse    2591   0.0 13.1  983333 187443  -  I    Mon01AM    7:12.01 ruby22: thin server (/home/discourse/discourse/tmp/sockets/thin.7.sock) (ruby22)

To stop your Sidekiq or Thin instances I highly recommend sending <code>SIGTERM</code> instead of <code>SIGKILL</code> to their processes and give them some time to clean-up gracefully:

    $ kill -SIGTERM 2576

If you are looking for an easier way to stop and monitor your Thin and Sidekiq instances, <code>sysutils/htop</code> is an viable option.


### Cron Jobs ###

Well, I am sure we cannot afford to run the script manually after each reboot, so we have to [set it up as a cron job](/blog/2015/06/11/the-proper-way-of-adding-a-cron-job/):

    $ crontab -e -u root

When your default editor appears, add this to the end of your cron jobs:

    # Discourse
    # At Boot
    @reboot     /home/discourse/cron/server.sh

Now to check whether your cron job has been added successfully or not, enter the following command:

    $ crontab -l

For your cron job to take effect:

    $ service cron restart

Now, after each reboot it will start automatically.


### Nginx Congiguration ###

I took the example Nginx configuration from <code>config/nginx.sample.conf</code> and adapt it to our example:

    # Discourse
    proxy_cache_path /usr/local/www/nginx/cache keys_zone=one:10m max_size=200m;

    # Discourse
    # Additional MIME types that you'd like nginx to handle go in here
    types {
        text/csv csv;
    }

    # Discourse
    log_format log_discourse '[$time_local] $remote_addr "$request" "$http_user_agent" "$sent_http_x_discourse_route" $status $bytes_sent "$http_referer" $upstream_response_time $request_time "$sent_http_x_discourse_username"';

    upstream discourse {
        server unix:/home/discourse/discourse/tmp/sockets/thin.0.sock;
        server unix:/home/discourse/discourse/tmp/sockets/thin.1.sock;
        server unix:/home/discourse/discourse/tmp/sockets/thin.2.sock;
        server unix:/home/discourse/discourse/tmp/sockets/thin.3.sock;
        server unix:/home/discourse/discourse/tmp/sockets/thin.4.sock;
        server unix:/home/discourse/discourse/tmp/sockets/thin.5.sock;
        server unix:/home/discourse/discourse/tmp/sockets/thin.6.sock;
        server unix:/home/discourse/discourse/tmp/sockets/thin.7.sock;
        #server 11011   # TCP/IP instead of Unix domain socket
    }

    server {
        error_log       /home/discourse/log/error.log;
        access_log      /home/discourse/log/access.log log_discourse;

        listen 80;
        gzip on;
        gzip_vary on;
        gzip_min_length 1000;
        gzip_comp_level 5;
        gzip_types application/json text/css application/x-javascript application/javascript;

        # Uncomment and configure this section for HTTPS support
        # NOTE: Put your ssl cert in your main nginx config directory (/etc/nginx)
        #
        # rewrite ^/(.*) https://enter.your.web.hostname.here/$1 permanent;
        #
        # listen 443 ssl;
        # ssl_certificate your-hostname-cert.pem;
        # ssl_certificate_key your-hostname-cert.key;
        # ssl_protocols TLSv1 TLSv1.1 TLSv1.2;
        # ssl_ciphers HIGH:!aNULL:!MD5;
        #

        server_name discuss.babaei.net discuss.fa.babaei.net;
        server_tokens off;

        sendfile on;

        keepalive_timeout 65;

        # maximum file upload size (keep up to date when changing the corresponding site setting)
        client_max_body_size 1m;

        # path to discourse's public directory
        set $public /home/discourse/discourse/public;

        # Prevent Internet Explorer 10 "compatibility mode", which breaks Discourse.
        # If other subdomains under your domain are supposed to use Internet Explorer Compatibility mode,
        # it may be used for this one too, unless you explicitly tell IE not to use it.  Alternatively,
        # some people have reported having compatibility mode "stuck" on for some reason.
        # (This will also prevent compatibility mode in IE 8 and 9, but those browsers aren't supported anyway.
        add_header X-UA-Compatible "IE=edge";

        # without weak etags we get zero benefit from etags on dynamically compressed content
        # further more etags are based on the file in nginx not sha of data
        # use dates, it solves the problem fine even cross server
        etag off;

        # prevent direct download of backups
        location ^~ /backups/ {
            internal;
        }

        # bypass rails stack with a cheap 204 for favicon.ico requests
        location /favicon.ico {
            return 204;
            access_log off;
            log_not_found off;
        }

        location / {
            root $public;
            add_header ETag "";

            # auth_basic on;
            # auth_basic_user_file /etc/nginx/htpasswd;

            location ~* assets/.*\.(eot|ttf|woff|woff2|ico)$ {
                expires 1y;
                add_header Cache-Control public;
                add_header Access-Control-Allow-Origin *;
            }

            location = /srv/status {
                access_log off;
                log_not_found off;
                proxy_set_header Host $http_host;
                proxy_set_header X-Real-IP $remote_addr;
                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header X-Forwarded-Proto $thescheme;
                proxy_pass http://discourse;
                break;
            }

            location ~ ^/assets/ {
                expires 1y;
                # asset pipeline enables this
                gzip_static on;
                add_header Cache-Control public;
                # TODO I don't think this break is needed, it just breaks out of rewrite
                break;
            }

            location ~ ^/plugins/ {
                expires 1y;
                add_header Cache-Control public;
            }

            # cache emojis
            location ~ /_?emoji.*\.(png|gif|jpg|jpeg)$/ {
                expires 1y;
                add_header Cache-Control public;
            }

            location ~ ^/uploads/ {
                # NOTE: it is really annoying that we can't just define headers
                # at the top level and inherit.
                #
                # proxy_set_header DOES NOT inherit, by design, we must repeat it,
                # otherwise headers are not set correctly
                proxy_set_header Host $http_host;
                proxy_set_header X-Real-IP $remote_addr;
                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header X-Forwarded-Proto $thescheme;
                proxy_set_header X-Sendfile-Type X-Accel-Redirect;
                proxy_set_header X-Accel-Mapping $public/=/downloads/;
                expires 1y;
                add_header Cache-Control public;

                ## optional upload anti-hotlinking rules
                #valid_referers none blocked mysite.com *.mysite.com;
                #if ($invalid_referer) { return 403; }

                # custom CSS
                location ~ /stylesheet-cache/ {
                    try_files $uri =404;
                }
                # this allows us to bypass rails
                location ~* \.(gif|png|jpg|jpeg|bmp|tif|tiff)$ {
                    try_files $uri =404;
                }
                # thumbnails & optimized images
                location ~ /_?optimized/ {
                    try_files $uri =404;
                }

                proxy_pass http://discourse;
                    break;
                }

                location ~ ^/admin/backups/ {
                    proxy_set_header Host $http_host;
                    proxy_set_header X-Real-IP $remote_addr;
                    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                    proxy_set_header X-Forwarded-Proto $thescheme;
                    proxy_set_header X-Sendfile-Type X-Accel-Redirect;
                    proxy_set_header X-Accel-Mapping $public/=/downloads/;
                    proxy_pass http://discourse;
                    break;
                }

                # This big block is needed so we can selectively enable
                # acceleration for backups and avatars
                # see note about repetition above
                location ~ ^/(letter_avatar/|user_avatar|highlight-js|stylesheets|favicon/proxied) {
                    proxy_set_header Host $http_host;
                    proxy_set_header X-Real-IP $remote_addr;
                    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                    proxy_set_header X-Forwarded-Proto $thescheme;

                    # if Set-Cookie is in the response nothing gets cached
                    # this is double bad cause we are not passing last modified in
                    proxy_ignore_headers "Set-Cookie";
                    proxy_hide_header "Set-Cookie";

                    # note x-accel-redirect can not be used with proxy_cache
                    proxy_cache one;
                    proxy_cache_valid 200 301 302 7d;
                    proxy_cache_valid any 1m;
                    proxy_pass http://discourse;
                    break;
                }

            location /letter_avatar_proxy/ {
                # Don't send any client headers to the avatars service
                proxy_method GET;
                proxy_pass_request_headers off;
                proxy_pass_request_body off;

                # Don't let cookies interrupt caching, and don't pass them to the
                # client
                proxy_ignore_headers "Set-Cookie";
                proxy_hide_header "Set-Cookie";

                proxy_cache one;
                proxy_cache_key $uri;
                proxy_cache_valid 200 7d;
                proxy_cache_valid 404 1m;
                proxy_set_header Connection "";

                proxy_pass http://discourse;
                break;
            }

            # we need buffering off for message bus
            location /message-bus/ {
                proxy_set_header Host $http_host;
                proxy_set_header X-Real-IP $remote_addr;
                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header X-Forwarded-Proto $thescheme;
                proxy_http_version 1.1;
                proxy_buffering off;
                proxy_pass http://discourse;
                break;
            }

            # this means every file in public is tried first
            try_files $uri @discourse;
        }

        location /downloads/ {
            internal;
            alias $public/;
        }

        location @discourse {
            proxy_set_header Host $http_host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header X-Forwarded-Proto $thescheme;
            proxy_pass http://discourse;
        }

        # Error Pages
        error_page  400              /400.html;
        location = /400.html {
            root   /usr/local/www/nginx/error;
        }
        error_page  401              /401.html;
        location = /401.html {
            root   /usr/local/www/nginx/error;
        }
        error_page  403              /403.html;
        location = /403.html {
            root   /usr/local/www/nginx/error;
        }
        error_page  404              /404.html;
        location = /404.html {
            root   /usr/local/www/nginx/error;
        }
        error_page  500 502 503 504  /50x.html;
        location = /50x.html {
            root   /usr/local/www/nginx/error;
        }
    }

    
### Troubleshooting ###

So, that's it if you did setup everything right, you must see the Discourse home page by entering e.g. [discuss.babaei.net](http://discuss.babaei.net/) or [discuss.fa.babaei.net](http://discuss.fa.babaei.net/) inside your browser. Otherwise, the first place to check are the log files that reside inside <code>/home/discourse/log/</code> and <code>/home/discourse/discourse/log/</code>. If you still do not have any clue why it's not working, make sure to double check that you did follow the tutorial correctly. Other than that, you are always welcome to discuss it in the comments section below.

