/**
 *
 * Provides some custom drush commands
 *
 */
class drush::config {

    file { "/usr/share/drush/commands/kala":
      ensure  => directory,
      mode    => 777,
      require => [Class["drush::install"], Class["drush::upgrade"]],
    }

    file { "/etc/drush":
      ensure  => directory,
      mode    => 777,
      require => [Class["drush::install"], Class["drush::upgrade"]],
    }

    file { "/usr/share/drush/commands/kala/kala.drush.inc":
      ensure  => file,
      mode    => 777,
      source  => "puppet:///modules/drush/kala.drush.inc",
      require => File["/usr/share/drush/commands/kala"],
    }

    file { "/etc/drush/drushrc.php":
      ensure  => file,
      mode    => 777,
      source  => "puppet:///modules/drush/drushrc.php",
      require => File["/etc/drush"],
    }
}
