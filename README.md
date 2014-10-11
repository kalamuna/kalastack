Kalastack 3!
=========================

Kalastack is a basic LEMP stack built for Drupal. At its core it is a series of puppet manifests that
are managed by Vagrant. Kalastack was built to run primarily on Ubuntu Server 12.04, though it will welcome multiple architectures in the future.

If you are interested in support for other architectures check out [Proviso](https://github.com/proviso/proviso)

## Installation

Kalastack 3 requires at least [Vagrant 1.3.5](http://downloads.vagrantup.com/tags/v1.3.5) and [VirtualBox 4.2.18](http://download.virtualbox.org/virtualbox/4.2.18/) to be run correctly. Before you begin please download both. If you are upgrading to Vagrant 1.5 you may need to go through the Vagrant update process.

**System Requirements:**
- Kalastack works on both 64 and 32 bit architectures and requires at least 2GB of ram.

*Notes:* At this time, Kalastack is actively tested on Mac OSX 10.9 and with Vagrant 1.6.3 and VirtualBox 4.3.12. It has also been used on Ubuntu 12.04 both natively and using VirtualBox and Vagrant. You may have to play around with the VT Intel settings on your machine to get it to work. That all said it is not a recommended or supported environment at this time.

*More Notes: On Ubuntu 12.04 with a Kernel of 3.9.0-x or greater, you may have issues with the 4.2.18 VBnot working properly.  This is resolved by using the a version of 4.3.x.

Once you have downloaded and installed both Vagrant and VirtualBox,
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

## Upgrading from Kalastack 2

Theoretically this should work but it hasn't been tested but here are the steps.

1. Upgrade your VirtualBox and Vagrant to at least the correct versions.   [Vagrant 1.3.5](http://downloads.vagrantup.com/tags/v1.3.5) and [VirtualBox 4.2.18](http://download.virtualbox.org/virtualbox/4.2.18/)
2. Checkout the latest version of 3.x aka

```bash
$ cd ~/kalastack
$ git fetch --all #This will grab the new branch
$ git checkout 3.x
  (or download and expand the latest 3.x tarball from https://github.com/kalamuna/kalastack/tags)
$ vagrant up --provison
```

Please contact us on whether this works or doesn't.

## Post Install Checks

### YOUR FILES

Kalastack uses NFS file sharing. You can access your server webroot at ~/kalabox/www on your host
machine. This way you can use your local IDE to edit files on your server.

## Working with Kalastack

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

Kalastack makes use of the [Terminatur](https://github.com/kalamuna/terminatur) which is built on top of the amazing [Terminus](https://github.com/pantheon-systems/terminus). Please
consult the [Terminatur Documentation](https://github.com/kalamuna/terminatur) for a complete run down on how to use Kalastack with your Pantheon sites.

### UPDATING YOUR HOST HOSTS FILE

Remember that the Kalastack does not automatically update the /etc/hosts file on
your host machine, so you'll need add each new site manually in order
to visit http://SITENAME.kala in your web browser! Kalastack does, however, manage the hosts
file in your VM.

1.3.3.7    SITENAME.kala

## Xdebug

Kalastack ships with xdebug for both debugging and profiling.

### DEBUGGING

Debugging is best done with an IDE such as netbeans or eclipse or with a text editor such as SublimeText.

The xdebug setup should already be done on the Kalastack end so you should
only need to set up your IDE. Here is some useful documentation for [eclipse](
http://brianfisher.name/content/drupal-development-environment-os-x-mamp-pro-eclipse-xdebug-and-drush), [netbeans](http://wiki.netbeans.org/HowToConfigureXDebug) and
[SublimeText](https://github.com/martomo/SublimeTextXdebug).

### PROFILING

For profiling, we recommend you use the webgrind client which comes preconfigured
with your Kalastack and is located at http://grind.kala.

Profiling on every page has a performance impact so you must trigger what pages
you want to profile by manually appending ?XDEBUG_PROFILE to
the URL (see [xdebug documentation](http://xdebug.org/docs/profiler) for more detail) and then
checking [webgrind](http://grind.kala).

Many browsers also offer automated tools/plugins to turn profiling on and off, i.e. [Xdebug helper](https://chrome.google.com/webstore/detail/xdebug-helper/eadndfjplgieldjbigjakmdgkmoaaaoc) for google Chrome.

### APACHE SOLR

Currently, Kalastack doesn't come with Solr installed by default. You can, however,
easily add it in by following the instructions on the [Adding Solr wiki page](https://github.com/kalamuna/kalastack/wiki/Adding-Solr-to-Kalastack).


-------------------------------------------------------------------------------------
(C) 2014 Kalamuna LLC
