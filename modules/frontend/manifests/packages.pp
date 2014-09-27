/**
 *
 * Install node packages.
 *
 */
class frontend::packages {

  exec { "nodepackages":
    path    => "/bin:/usr/bin",
    unless  => "which npm",
    command => "npm install -g coffee-script bower grunt-cli gulp component yo",
    require => Class["frontend::install"],
  }

}
