# Kalstack
=========================

Kalastack is a basic LEMP stack built for Drupal. At its core it is a series of puppet manifests that
are managed by Vagrant. Kalastack was built to run primarily on Ubuntu Server 12.04. 

## Quickstart

Kalastack requires [Vagrant 1.1.2](http://downloads.vagrantup.com/tags/v1.1.2) and [VirtualBox 4.28](http://download.virtualbox.org/virtualbox/4.2.8/) to be run correctly. Before you begin please download both. 
Notes: At this time, Kalastack is actively tested on Mac OSX 1.8 and with Vagrant 1.1.2 and VirtualBox 4.2.8. 

Once you have downloaded and installed both Vagrant and Virtual box,
you can build out the complete stack:

    $ mkdir ~/kalastack
    $ cd ~/kalastack
    $ git clone git://github.com/kalamuna/kalastack.git ./
    $ vagrant box add kalabox http://files.vagrantup.com/precise64.box
    $ vagrant up kalabox --provision-with=shell,puppet_server

To ssh into your server, from within ~/kalastack, issue:

    $ vagrant ssh 

## Post Install Checks

### VHOSTS

Add the following entry to /etc/hosts on your host system
  
    192.168.42.10 start.kala php.kala grind.kala kala

On Windows XP this is located at c:\WINDOWS\system32\drivers\etc\hosts

You should now be able to access http://start.kala in your browser

### YOUR FILES

Kalastack uses NFS file sharing. You can access your server webroot at ~/kalabox/www on your host
machine. This way you can use your local IDE to edit files on your server. 

## Working with Pantheon

### SITE ALIASES

The first step to working with Pantheon is to get your site aliases. These are 
available for download on your Pantheon account page. You will need to rename and put the 
downloaded file into ~/kalabox/drush/aliases.drushrc.php on your host machine. You can verify 
your aliases are functioning correctly by running "drush sa" on your Kalastack.

## SSH KEYS

You are also going to want to make sure you create and add your Kalabox ssh public key to 
Pantheon. This can be a little tricky. See [how to participate](https://github.com/kalamuna/kalastack/wiki/How-to-Participate#ssh-key) for more info

    $ ssh-keygen
    $ cat ~/.ssh/id_rsa.pub

## DRUSH

Kalastack ships with 8 custom drush commands designed specifically for Pantheon 
and Kalastack. They are useless without Pantheon's site alias file.
 
These commands only work with your dev environments. You will use the same 
naming convention as your pantheon aliases 	(PANTHEON.SITENAME.ENV) but you will 
omit the @. You are using the alias name as an argument, not as an alias.
Here are the commands.

     $ drush build SITENAME.dev   

Will completely build your Pantheon site on your Kalastack, this will 
edit settings.php and set up a vhost. After running this command and
adding your server name to your hosts /etc/hosts file you should be
able to visit the site in your web browser.

    $ drush krefresh SITENAME.dev 

Will refresh the code, database and files on your Kalastack from your 
pantheon site

    $ drush crush SITENAME.dev

Will completely remove SITENAME.dev from your Kalastack.

    $ drush kala

Will show helpful info

    $ drush code SITENAME.dev    

Will either git clone or git pull from your Pantheon codebase to your 
Kalabox at /var/www/SITENAME on your guest and ~/kalabox/www/SITENAME 
on your guest.

    $ drush data SITENAME.dev    

Will download and import your Pantheon dev MySQL database to your 
Kalabox in a DB named SITENAME_kala

    $ drush files SITENAME.dev   

Will sync your pantheon dev files to your Kalastack, accessible from 
/var/www/SITENAME/sites/default/files when ssh'd in to your stack, and from
~/kalabox/www/SITENAME/sites/default/files on your host.

    $ drush vhost SITENAME.dev   

Will build and enable a nginx vhost file of your Pantheon site on your 
Kalastack at SITENAME.kala


### UPDATING YOUR HOST HOSTS FILE

Remember that the Kalastack does not automatically update the /etc/hosts file on 
your HOST so you will have to add each new site line manually in order 
to visit http://SITENAME.kala in your web browser!

    192.168.42.10    SITENAME.kala

## Xdebug

Kalastack ships with xdebug for both debugging and profiling. 

### DEBUGGING

Debugging is best done with an IDE such as netbeans or eclipse on your host OS. 
The xdebug setup should already be done on the Kalabox end so you should 
only need to set up your IDE. 

Here is some useful documentation to help:
http://brianfisher.name/content/drupal-development-environment-os-x-mamp-pro-eclipse-xdebug-and-drush
http://wiki.netbeans.org/HowToConfigureXDebug

### PROFILING

For profiling, we recommend you use the webgrind client which comes preconfigured
with your Kalabox and is located at http://grind.kala.

Profiling on every page has a performance impact so you must trigger what pages
you want to profile by manually appending ?XDEBUG_PROFILE to 
the URL (see http://xdebug.org/docs/profiler for more detail) and then 
checking [webgrind](http://grind.kala). 

Many broswers also offer automated tools/plugins to turn profiling on and off. 
https://chrome.google.com/webstore/detail/xdebug-helper/eadndfjplgieldjbigjakmdgkmoaaaoc


################################################################################

(C) 2013 Kalamuna LLC
