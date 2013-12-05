/**
 *
 * Installs Terminus
 *
 */
class drush::refresh {

  exec { "drushpurge":
    path    => "/bin:/usr/bin",
    command => "rm -rf /home/$::kalauser/.drush/cache/default",
    subscribe => Exec["installterminatur"],
  }

  exec { "drushclear":
    path    => "/bin:/usr/bin",
    command => "drush cache-clear drush",
    subscribe => Exec["installterminatur"],
  }

}
