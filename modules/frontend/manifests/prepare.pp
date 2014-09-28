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

  file { "/etc/apt/sources.list.d/rubyedge.list":
    ensure => file,
    source => "puppet:///modules/frontend/rubyedge.list",
  }

  exec { "keydir":
    unless  => "ls -a /home/$::kalauser | grep .gnupg",
    path    => "/bin:/usr/bin",
    command => "mkdir /home/$::kalauser/.gnupg",
  }

  exec { "rubykey":
    path    => "/bin:/usr/bin",
    unless  => "apt-key list | grep 1024R/C3173AA6",
    command => "sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 80F70E11F0F0D5F10CB20E62F5DA5F09C3173AA6",
    require => Exec["keydir"],
  }

  exec { "apt-refresh":
    command => "/usr/bin/apt-get update -y",
    subscribe => File["/etc/apt/sources.list.d/rubyedge.list"],
    require => Exec["rubykey"],
  }

}
