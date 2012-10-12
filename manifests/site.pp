node "default" {
	# set a static ip for our webserver
    # NOT DOING THIS YET
    #
    # network::interface { box:
	# 	style => webserver,
    # }
   
    # initialize core packages
    include network
    include puppet
    include ssh
    include git
    include samba
    
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
	
	# build basic drupal site
	drupal::nginx::vhost { "drupaldefault":
        server_name => "kala",
        root        => "/var/www/drupal",
        enabled     => "FALSE",
        custom      => "# THIS IS MEANT TO BE USED FOR BUILDING OTHER DRUPAL VHOSTS"
    }
}
