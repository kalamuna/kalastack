Kalastack
=========================

Kalastack is a basic LEMP stack built for Drupal. At its core it is a series of puppet manifests that
are managed by Vagrant. Kalastack was built to run primarily on Ubuntu Server 12.04, though it will welcome to multiple architectures in the future.

## Quickstart

Kalastack requires [Vagrant 1.1.2](http://downloads.vagrantup.com/tags/v1.1.2) and [VirtualBox 4.2.8](http://download.virtualbox.org/virtualbox/4.2.8/) to be run correctly. Before you begin please download both.

*Notes:* At this time, Kalastack is actively tested on Mac OSX 10.8 and with Vagrant 1.1.2 and VirtualBox 4.2.8.

Once you have downloaded and installed both Vagrant and Virtual box,
you can build out the complete stack:

```bash
$ mkdir ~/kalastack
$ cd ~/kalastack
$ git clone git://github.com/kalamuna/kalastack.git ./
$ vagrant box add kalabox http://files.vagrantup.com/precise64.box
$ vagrant up kalabox --provision-with=shell,puppet_server
```
To ssh into your server, from within ~/kalastack, issue:
```bash
$ vagrant ssh
```
## Post Install Checks

### VHOSTS

Add the following entry to /etc/hosts on your host system. On Windows XP this is located at c:\WINDOWS\system32\drivers\etc\hosts

    192.168.42.10 start.kala php.kala grind.kala kala

You should now be able to access http://start.kala in your browser!


### YOUR FILES

Kalastack uses NFS file sharing. You can access your server webroot at ~/kalabox/www on your host
machine. This way you can use your local IDE to edit files on your server.

## Working with Pantheon

### SITE ALIASES

Download your aliases from within the Pantheon dashboard, then move and rename the alias file from ```pantheon.aliases.drushrc.php``` to ```aliases.drushrc.php``` and put it in ```/kalabox/drush/```
```bash
$ mv pantheon.aliases.drushrc.php /kalabox/drush/aliases.drushrc.php
```

You can verify your aliases are functioning correctly by running on your Kalastack:
```bash
$ drush sa
```


## SSH KEYS

if you want to test Pantheon integration, you will need to make sure that your kalabox SSH key is associated with your account. Kalabox will very soon [use Vagrant to forward your native OS's SSH key](http://docs.vagrantup.com/v2/vagrantfile/ssh_settings.html), but for now you need to manually copy your ssh key into the box. You will need to redo this EVERY TIME you recreate the box (for now).

Logged into your host machine shell:
```bash
$ cp -r ~/.ssh ~/kalabox/www/
```
Then, log into the box and copy the keys:
```bash
$ vagrant ssh
$ cp -r /var/www/.ssh ~/
```


## DRUSH

Kalastack ships with 8 custom drush commands designed specifically for Pantheon
and Kalastack. They depend on a Pantheon site alias file.

These commands only work with your dev environments. You will pass your kalabox site as an
argument to these commands. Site names are derived from the pantheon aliases file on your Kalastack and interact with your Pantehon DEV environment.

     $ drush build SITENAME.dev

Will completely build your Pantheon site on your Kalastack, this will
edit settings.php and set up a vhost. After running this command and
adding your server name to your hosts /etc/hosts file you should be
able to visit the site in your web browser.
```bash
$ drush krefresh SITENAME.dev
```
Will refresh the code, database and files on your Kalastack from your
pantheon site
```bash
$ drush crush SITENAME.dev
```
Will completely remove SITENAME.dev from your Kalastack.
```bash
$ drush code SITENAME.dev
```
Will either git clone or git pull from your Pantheon codebase to your
Kalabox at /var/www/SITENAME on your guest and ~/kalabox/www/SITENAME
on your host.
```bash
$ drush data SITENAME.dev
```
Will download and import your Pantheon dev MySQL database to your
Kalabox in a DB named SITENAME_kala
```bash
$ drush files SITENAME.dev
```
Will sync your pantheon dev files to your Kalastack, accessible from
/var/www/SITENAME/sites/default/files when ssh'd in to your stack, and from
~/kalabox/www/SITENAME/sites/default/files on your host.
```bash
$ drush vhost SITENAME.dev
```
Will build and enable a nginx vhost file of your Pantheon site on your
Kalastack at SITENAME.kala
```bash
$ drush kala
```
Will show helpful info

### UPDATING YOUR HOST HOSTS FILE

Remember that the Kalastack does not automatically update the /etc/hosts file on
your machine, so you'll need add each new site manually in order
to visit http://SITENAME.kala in your web browser!

    192.168.42.10    SITENAME.kala


## Xdebug

Kalastack ships with xdebug for both debugging and profiling.

### DEBUGGING

Debugging is best done with an IDE such as netbeans or eclipse on your host OS.
The xdebug setup should already be done on the Kalabox end so you should
only need to set up your IDE. Here is some useful documentation [for eclipse](
http://brianfisher.name/content/drupal-development-environment-os-x-mamp-pro-eclipse-xdebug-and-drush) and [netbeans](http://wiki.netbeans.org/HowToConfigureXDebug) to help.

### PROFILING

For profiling, we recommend you use the webgrind client which comes preconfigured
with your Kalabox and is located at http://grind.kala.

Profiling on every page has a performance impact so you must trigger what pages
you want to profile by manually appending ?XDEBUG_PROFILE to
the URL (see [xdebug documentation](http://xdebug.org/docs/profiler) for more detail) and then
checking [webgrind](http://grind.kala).

Many broswers also offer automated tools/plugins to turn profiling on and off, i.e. [Xdebug helper](https://chrome.google.com/webstore/detail/xdebug-helper/eadndfjplgieldjbigjakmdgkmoaaaoc) for google Chrome.


## Working with Kalabox

###Start/Stop

Don't start the box in Virualbox, but instead, from within the kalastack codebase use the command line to spin up the stack:
```bash
$ vagrant up --no-provision
```
and log in via:
```bash
$ vagrant ssh
```
and spin down the box with:
```bash
$ vagrant halt
```

  
-------------------------------------------------------------------------------------
(C) 2013 Kalamuna LLC
