
define phpfpm::extension {
  
  package { "${name}":
    ensure => present,
    require => Class["phpfpm::install"],
    notify => [Class["phpfpm::service"], Class["nginx::service"]],
  }
  
}
