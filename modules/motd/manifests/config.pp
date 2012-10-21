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
    content => template("motd/10-help-text.erb"),
    owner => "root",
    group => "root",
  }
  
  file { "/etc/update-motd.d/60-kala-help" :
    ensure => present,
    content => template("motd/60-kala-help.erb"),
    owner => "root",
    group => "root",
  }
  
  file { "/etc/update-motd.d/90-updates" :
    ensure => absent,
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