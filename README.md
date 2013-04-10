# Kalstack
=========================

Kalastack is a basic LEMP stack built for Drupal. At its core it is a series of puppet manifests that
are managed by Vagrant. Kalastack was built to run primarily on Ubuntu Server 12.04. 

## Quickstart

Kalastack requires Vagrant and VirtualBox to be run correctly. Before you begin please download both. 
Notes: This has only been tested on Mac OSX 1.8 and with Vagrant 1.1.2 and VirtualBox 4.2.8. 

Once you have downloaded and installed both Vagrant and Virtual box please do the following:

1. mkdir ~/kalastack
2. cd ~/kalastack
3. git clone git://github.com/kalamuna/kalastack.git ./
4. vagrant box add kalabox http://files.vagrantup.com/precise64.box
5. vagrant up kalabox --provision-with=shell,puppet_server

This should build out the complete stack. To ssh into your server run vagrant ssh from ~/kalastack.

## Post Install Checks

### VHOSTS

Add the following entry to /etc/hosts  
  
  192.168.42.10 start.kala php.kala grind.kala kala

* On Windows XP this is located at c:\WINDOWS\system32\drivers\etc\hosts

### YOUR FILES

Kalastack uses NFS file sharing. You can access your server webroot at ~/kalabox/www on you host
machine. This way you can use your local IDE to edit files on your server. 

## Working with Pantheon

### SITE ALIASES

The first step to working with Pantheon is to get your site aliases. These are 
available for download on your Pantheon account page. You will need to put the 
downloaded file into ~/kalabox/drush on your host machine. You can verify that they are 
functioning correctly by running "drush sa" on your Kalastack.

## SSH KEYS

You are also going to want to make sure you creat and add your Kalabox ssh public key to 
pantheon. 

  ssh-keygen
  cat ~/.ssh/id_rsa.pub

## DRUSH

Kalastack ships with 8 custom drush commands designed specifically for Pantheon 
and Kalastack. They are useless without Pantheon's site alias file.
 
These commands only work with your dev environments. You will use the same 
naming convention as your pantheon aliases 	(PANTHEON.SITENAME.ENV) but you will 
omit the @. You are using the alias name as an argument, not as an alias.
Here are the commands.

	1. drush build SITENAME.dev   

		Will completely build your pantheon site on your Kalastack, this will 
		edit settings.php and set up a vhost. After running this command and
		adding your server name to your hosts /etc/hosts file you should be
		able to browse to the site.

	2. drush krefresh SITENAME.dev 

		Will refresh the code, database and files on your Kalastack from your 
		pantheon site

	3. drush crush SITENAME.dev

		Will completely remove SITENAME.dev from your Kalastack.
		
	4. drush kala
    
    Will show helpful info
        
	5. drush code SITENAME.dev    

		Will either git clone or git pull from your pantheon codebase to your 
		Kalabox at /var/www/SITENAME on your guest and ~/kalabox/www/SITENAME 
    on your guest.
    
	6. drush data SITENAME.dev    

		Will either download and import from your pantheon database to your 
		Kalabox at kala:SITENAME_kala
		
	7. drush files SITENAME.dev   

		Will sync your pantheon files to your Kalastack at 
		/var/www/SITENAME/sites/default/files on your stack and
    ~/kalabox/www/SITENAME/sites/default/files on your host.
		
	8. drush vhost SITENAME.dev   

		Will build and enable a nginx vhost file of your pantheon site on your 
		Kalastack at SITENAME.kala

### UPDATING YOUR HOST HOSTS FILE

Remember that the Kalastack does not automatically update the /etc/hosts file on 
your HOST so you will have to add the following line manually.

	"192.168.42.10    SITENAME.kala"

You should now be able to navigate to SITENAME.kala in your browser and get to 
your site! 

## Xdebux

Kalastack ships with xdebug for both debugging and profiling. 

### DEBUGGING

For debugging we recommend you use an IDE on your host OS such as netbeans or
eclipse. The xdebug setup should already be done on the Kalabox end so you should 
only need to set up your IDE. 

Here is some useful documentation to help:
http://brianfisher.name/content/drupal-development-environment-os-x-mamp-pro-eclipse-xdebug-and-drush
http://wiki.netbeans.org/HowToConfigureXDebug

### PROFILING

For profiling we recommend you use the webgrind client which comes preconfigured
with your Kalabox and is located at grind.kala.

Profiling on every page has a performance impact so you must trigger what pages
you want to profile. You can do this manually by appending ?XDEBUG_PROFILE to 
the URL (see http://xdebug.org/docs/profiler for more detail) and then 
checking webgrind. 

Many broswers also offer tools/plugins to turn profiling on and off. 
https://chrome.google.com/webstore/detail/xdebug-helper/eadndfjplgieldjbigjakmdgkmoaaaoc


################################################################################

(C) 2012 Kalamuna LLC
