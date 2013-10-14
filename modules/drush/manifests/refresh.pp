/**
 *
 * Installs Terminus
 *
 */
class drush::refresh {

  exec { "drushrefresh":
    path    => "/bin:/usr/bin",
    command => "drush cache-clear drush",
    subscribe => [Exec["installterminus"], Exec["installterminatur"]],
  }

}
