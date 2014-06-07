/**
 *
 * Installs Terminus
 *
 */
class drush::composer {

  exec { "installcomposer":
    path    => "/bin:/usr/bin",
    unless  => "ls /usr/local/bin | grep composer",
    command => "curl -sS https://getcomposer.org/installer | php && mv composer.phar /usr/local/bin/composer",
    require => [Class["phpfpm::extensions::curl"], Class["phpfpm::extensions::apc"], Class["php5::install"]],
  }

}
