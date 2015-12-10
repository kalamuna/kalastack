/**
 *
 * Install node packages.
 *
 */
class frontend::packages {

  exec { "nodepackages":
    path    => "/bin:/usr/bin",
    unless  => "npm list -g --depth=0 | grep grunt-cli",
    command => "sudo npm install -g coffee-script bower grunt-cli gulp",
    require => Exec["preparepackages"],
  }

  exec { "preparepackages":
    path    => "/bin:/usr/bin",
    unless  => "npm config list | grep prefix",
    command => "sudo -u$::kalauser mkdir /home/$::kalauser/.npm && npm config set prefix /home/$::kalauser/.npm",
    require => Class["frontend::install"],
  }

}
