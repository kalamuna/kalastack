/**
 *
 * Sets our PPA things and also sets the node prefix so we dont have to
 * sudo install our global pacakges
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
