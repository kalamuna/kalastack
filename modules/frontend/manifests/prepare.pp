/**
 *
 * Sets our PPA things
 *
 */
class frontend::prepare {

  exec { "preparenode":
    path    => "/bin:/usr/bin",
    unless  => "which node",
    command => "curl -sL https://deb.nodesource.com/setup | sudo bash -",
    require => Class["phpfpm::extensions::curl"],
  }

}
