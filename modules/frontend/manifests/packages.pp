/**
 *
 * Install node packages.
 *
 */
class frontend::packages {

  exec { "nodepackages":
    path    => "/bin:/usr/bin",
    command => "echo Node.js $(node --version) - npm $(npm --version)",
    require => Exec["preparepackages"],
  }

  exec { "preparepackages":
    path    => "/bin:/usr/bin",
    unless  => "npm config list | grep prefix",
    command => "mkdir /home/$::kalauser/.npm && npm config set prefix /home/$::kalauser/.npm",
    require => Class["frontend::install"],
  }

}
