/**
 * 
 * Installs and configures nginx
 * 
 */
class user::config {
    
  file { "/home/${::kala_user}/.profile" :
      ensure => present,
      content => template("user/profile.erb"),
      owner => "${::kala_user}",
      group => "${::kala_user}",
      require => Class["ssh::server::install"],
    }
  
}