class drush::config {
    
    file { "~/.drush":
      ensure => directory,
      owner  => www-data,
      group  => www-data,
      mode   => 777,
    }
    
    file { "~/.drush/index.php":
      ensure  => file,
      owner   => www-data,
      group   => www-data,
      mode    => 777,
      source  => "puppet:///modules/drush/createvhost.drush.inc",
      require => File["~/.drush"],
    }
    
}