/**
 *
 * Installs drush
 *
 */
class drush::install {

  exec { "install drush":
    path    => "/bin:/usr/bin:/usr/local/bin",
    unless  => "ls /usr/bin | grep drush",
    command => "composer global require drush/drush:dev-master",
    require => Class["drush::composer"],
  }

}
