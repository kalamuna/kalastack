/**
 * 
 * Provides some custom drush commands
 * 
 */
class drush::config {
    
    file { "/usr/share/drush/commands/kala":
      ensure => directory,
      owner  => root,
      group  => root,
      mode   => 755,
    }
    
    file { "/usr/share/drush/commands/kala/createvhost.drush.inc":
      ensure  => file,
      owner   => root,
      group   => root,
      mode    => 644,
      source  => "puppet:///modules/drush/createvhost.drush.inc",
      require => File["/usr/share/drush/commands/kala"],
    }
    
}