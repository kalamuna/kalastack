/**
 * 
 * This will build a basic LEMP stack with some extra goodies for every node that connects to the puppetmaster
 * at kalabox.kalamuna.com
 * 
 */

node "default" {
       
  # initialize core packages
  include user
  include network
  include puppet
  include ssh
  include git
  include samba
  include motd
  include unzip
  
  # initialize LEMP stack
  include phpfpm
    
	phpfpm::nginx::kalabox { "default":
	    server_name => "kala",
	    root        => "/var/www",
	}
	include mysql
	
	# initialize bonus shit
	include solr
	include drush
	include phpmyadmin
	include webgrind
	
	# build basic drupal site
	drupal::nginx::vhost { "drupaldefault":
        server_name => "drupal.kala",
        root        => "/var/www/drupal",
        enabled     => "FALSE",
        custom      => "# THIS IS MEANT TO BE USED FOR BUILDING OTHER DRUPAL VHOSTS"
    }
    
}
