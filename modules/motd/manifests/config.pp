/**
 * 
 * Installs and configures nginx
 * 
 */
class motd::config {
    
  # replace welcome to ubuntu with welcome to kalabox
  file { "/etc/update-motd.d/00-header" :
    ensure => present,
    content => template("motd/00-header.erb"),
    owner => "root",
    group => "root",
  }
  
  # replace ubuntu docs with kalabox docs
  file { "/etc/update-motd.d/10-help-text" :
    ensure => present,
    mode => 0755,
    content => template("motd/10-help-text.erb"),
    owner => "root",
    group => "root",
  }
  
  file { "/etc/update-motd.d/05-kala-help" :
    ensure => present,
    mode => 0755,
    content => template("motd/05-kala-help.erb"),
    owner => "root",
    group => "root",
  }
  
  file { "/etc/update-motd.d/90-updates-available" :
    ensure => absent,
    mode => 0755,
    owner => "root",
    group => "root",
  }
  
  file { "/etc/update-motd.d/91-release-upgrade" :
    ensure => absent,
    owner => "root",
    group => "root",
  }
  
  file { "/etc/update-motd.d/98-fsck-at-reboot" :
    ensure => absent,
    owner => "root",
    group => "root",
  }
  
  file { "/etc/update-motd.d/98-reboot-required" :
    ensure => absent,
    owner => "root",
    group => "root",
  }
  
}