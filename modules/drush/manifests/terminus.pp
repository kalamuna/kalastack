/**
 *
 * Installs Terminus
 *
 */
class drush::terminus {

  exec { "installcomposer":
    path    => "/bin:/usr/bin",
    unless  => "ls /usr/local/bin | grep composer",
    command => "curl -sS https://getcomposer.org/installer | php && mv composer.phar /usr/local/bin/composer",
    require => [Class["drush::upgrade"], Class["phpfpm::extensions::curl"], Class["phpfpm::extensions::apc"]],
  }

  exec { "installterminus":
    path    => "/bin:/usr/bin",
    unless  => "drush | grep pantheon-auth",
    command => "mkdir /usr/share/drush/commands/terminus && /usr/local/bin/composer create-project pantheon-systems/terminus /usr/share/drush/commands/terminus -s dev --no-dev -n && drush cache-clear drush",
    require => Exec["installcomposer"],
  }

}
