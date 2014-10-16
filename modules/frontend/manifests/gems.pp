/**
 *
 * Install ruby gemz.
 *
 */
class frontend::gems {

  exec { "compass":
    path    => "/bin:/usr/bin",
    unless  => "gem list | grep 'compass (0.12.3)'",
    command => "sudo gem install compass --version 0.12.3",
    require => Class["frontend::install"],
  }

}
