Kalastack 3!
=========================

Kalastack is a basic LEMP stack built for Drupal. At its core it is a series of puppet manifests that
are managed by Vagrant. Kalastack was built to run primarily on Ubuntu Server 12.04, though it will welcome multiple architectures in the future.

## Quickstart

Kalastack requires [Vagrant 1.3.3](http://downloads.vagrantup.com/tags/v1.3.3) and [VirtualBox 4.2.18](http://download.virtualbox.org/virtualbox/4.2.18/) to be run correctly. Before you begin please download both.

**System Requirements:**
- Kalastack works on both 64 and 32 bit architectures and requires at least 2GB of ram.

*Notes:* At this time, Kalastack is actively tested on Mac OSX 10.8 and with Vagrant 1.3.3 and VirtualBox 4.2.18. It has also been used on Ubuntu 12.04 both natively and using VirtualBox and Vagrant. You may have to play around with the VT Intel settings on your machine to get it to work. That all said it is not a recommended or supported environment at this time.

Once you have downloaded and installed both Vagrant and Virtual box,
you can build out the complete stack:

```bash
$ mkdir ~/kalastack
$ cd ~/kalastack
$ git clone git://github.com/kalamuna/kalastack.git ./
  (or download and expand the latest 3.x tarball from https://github.com/kalamuna/kalastack/tags)
$ vagrant plugin install vagrant-hostsupdater
$ vagrant up
```

You should now be able to access http://start.kala in your browser!

To ssh into your server, from within ~/kalastack, issue:
```bash
$ vagrant ssh
```
## Post Install Checks

### YOUR FILES

Kalastack uses NFS file sharing. You can access your server webroot at ~/kalabox/www on your host
machine. This way you can use your local IDE to edit files on your server.

## Working with Kalabox

###Start/Stop

Don't start the box in Virualbox, but instead, from within the kalastack codebase use the command line to spin up the stack:
```bash
$ vagrant up
```
and log in via:
```bash
$ vagrant ssh
```
and spin down the box with:
```bash
$ vagrant halt
```

## Working with Pantheon

## DRUSH

Kalastack ships with 8 custom drush commands. These commands are used primarily to interact with your Pantheon sites however they can also be used to spin up a new site.
You will need to have valid pantheon aliases to take advantage of the pantheon integration. See above for instructions on using your aliases with Kalastack.

These commands only work with your dev environments. You will pass your kalabox site as an
argument to these commands. Site names are derived from the pantheon aliases file on your Kalastack and interact with your Pantehon DEV environment.

```bash
$ drush build SITENAME.dev # This will pull down and build a pantheon site defined in your aliases file on your Kalastack
$ drush build SITENAME # This will spin up a new Panopoly site at SITENAME.kala with user:admin, pass:admin
$ drush build SITENAME --profile=MYDISTRO # this will spin up a new MYSDISTRO site at SITENAME.kala with user:admin, pass:admin
```
Drush build will either completely build your Pantheon site on your Kalastack or spin up a new site. This will
edit settings.php and set up a vhost as needed. After running this command and
adding your server name to your hosts /etc/hosts file you should be
able to visit the site in your web browser.
```bash
$ drush krefresh SITENAME.dev
```
Will refresh the code, database and files on your Kalastack from your
pantheon site
```bash
$ drush crush SITENAME.dev # Will remove a Pantheon site from your Kalastack
$ drush crush SITENAME # Will remove a site from your Kalastack
```
Will completely remove SITENAME.dev or SITENAME from your Kalastack.
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

### UPDATING YOUR HOST HOSTS FILE

Remember that the Kalastack does not automatically update the /etc/hosts file on
your machine, so you'll need add each new site manually in order
to visit http://SITENAME.kala in your web browser!

    1.3.3.7    SITENAME.kala


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

Many browsers also offer automated tools/plugins to turn profiling on and off, i.e. [Xdebug helper](https://chrome.google.com/webstore/detail/xdebug-helper/eadndfjplgieldjbigjakmdgkmoaaaoc) for google Chrome.

### APACHE SOLR

Currently, Kalastack doesn't come with Solr installed by default. You can, however,
easily add it in by following the instructions on the [Adding Solr wiki page](https://github.com/kalamuna/kalastack/wiki/Adding-Solr-to-Kalastack).


-------------------------------------------------------------------------------------
(C) 2013 Kalamuna LLC
