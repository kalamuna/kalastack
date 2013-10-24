/**
 *
 * Installs Terminatur
 *
 */
class drush::terminatur {

  exec { "installterminatur":
    path    => "/bin:/usr/bin",
    unless  => "drush | grep terminatur-aliases",
    command => "mkdir /usr/share/drush/commands/terminatur && /usr/local/bin/composer create-project kalamuna/terminatur /usr/share/drush/commands/terminatur -s dev --no-dev -n",
    require => Exec["installcomposer"],
  }

}
