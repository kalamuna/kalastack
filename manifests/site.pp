
/**
 *
 * This will build a basic LEMP stack with some extra goodies for every node that connects
 * to the puppetmaster at kalabox.kalamuna.com
 */

node /^kala\.[a-f0-9]{32}\.box$/  {
  # initialize core packages
  include apt
  include git
  include unzip
  include nfs

  # initialize LEMP stack
  include phpfpm

  phpfpm::nginx::kalabox { "default":
    server_name => "start.kala",
    root        => "/usr/share/kalabox",
  }
  include mysql

  # initialize bonus shit
  # include solr
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
