/**
 *
 * Provides some custom drush commands
 *
 */
class drush::config {
  file { "/etc/drush":
    ensure  => directory,
    mode    => 777,
    require => Class["drush::install"],
  }

  file { "/etc/drush/drushrc.php":
    ensure  => file,
    mode    => 777,
    source  => "puppet:///modules/drush/drushrc.php",
    require => File["/etc/drush"],
  }
}
