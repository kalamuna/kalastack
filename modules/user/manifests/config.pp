/**
 *
 * Provides some custom cnfig
 */
class user::config {

  file { "/home/$::kalauser/.colors":
    ensure => file,
    mode   => 755,
    owner  => $::kalauser,
    group  => $::kalauser,
    source => "puppet:///modules/user/.colors",
  }

  file { "/home/$::kalauser/.bashrc.kala":
    ensure => file,
    mode   => 755,
    owner  => $::kalauser,
    group  => $::kalauser,
    source => "puppet:///modules/user/.bashrc.kala",
  }
  
  file { "/home/$::kalauser/.kalabash":
    ensure => file,
    mode   => 755,
    owner  => $::kalauser,
    group  => $::kalauser,
    source => "puppet:///modules/user/.kalabash",
  }

  file { "/home/$::kalauser/.ssh/config":
    ensure => file,
    mode   => 755,
    owner  => $::kalauser,
    group  => $::kalauser,
    source => "puppet:///modules/user/ssh-config",
  }
  
  exec { "extendbashrc":
    path    => "/bin:/usr/bin",
    unless  => "cat /home/$::kalauser/.bashrc | grep kalabash",
    command => "cat /home/$::kalauser/.bashrc.kala >> /home/$::kalauser/.bashrc",
    require => File["/home/$::kalauser/.bashrc.kala"],
  }
  
  # Thanks @tizzo!
  user { "$::kalauser": 
    groups => ['dialout'] 
  }

}