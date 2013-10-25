/**
 *
 * Installs Terminatur
 *
 */
class drush::terminatur {

  exec { "installterminatur":
    path    => "/bin:/usr/bin",
    unless  => "drush | grep terminatur-aliases",
    command => "mkdir /usr/share/drush/commands/terminatur && /usr/local/bin/composer create-project kalamuna/terminatur /usr/share/drush/commands/terminatur 1.0-alpha2 --no-dev -n",
    require => Exec["installcomposer"],
  }

}
