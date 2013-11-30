/**
 *
 * Installs Terminus
 *
 */
class drush::refresh {

  exec { "drushrefresh":
    path    => "/bin:/usr/bin",
    command => "rm -rf /home/$::kalauser/.drush/cache/default",
    subscribe => Exec["installterminatur"],
  }

}
