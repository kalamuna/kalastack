/**
 *
 * Installs Terminatur
 *
 */
class drush::terminatur {

  exec { "installterminatur":
    path    => "/bin:/usr/bin",
    unless  => "cat /usr/share/drush/commands/terminatur/composer.lock | grep $::terminatur_version",
    command => "sudo rm -rf /usr/share/drush/commands/terminatur && /usr/local/bin/composer create-project kalamuna/terminatur /usr/share/drush/commands/terminatur $::terminatur_version --no-dev -n",
    require => Exec["installcomposer"],
  }

}
