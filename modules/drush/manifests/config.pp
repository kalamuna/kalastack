/**
 * 
 * Provides some custom drush commands
 * 
 */
class drush::config {
    
    file { "/usr/share/drush/commands/kala":
      ensure  => directory,
      owner   => root,
      group   => root,
      mode    => 755,
      require => Class["drush::install"],
    }
    
    file { "/usr/share/drush/commands/kala/kala.drush.inc":
      ensure  => file,
      owner   => root,
      group   => root,
      mode    => 644,
      source  => "puppet:///modules/drush/kala.drush.inc",
      require => File["/usr/share/drush/commands/kala"],
    }
    
}