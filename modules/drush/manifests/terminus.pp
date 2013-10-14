/**
 *
 * Installs Terminus
 *
 */
class drush::terminus {

  exec { "installterminus":
    path    => "/bin:/usr/bin",
    unless  => "drush | grep pantheon-auth",
    command => "mkdir /usr/share/drush/commands/terminus && /usr/local/bin/composer create-project pantheon-systems/terminus /usr/share/drush/commands/terminus -s dev --no-dev -n",
    require => Exec["installcomposer"],
  }

}
