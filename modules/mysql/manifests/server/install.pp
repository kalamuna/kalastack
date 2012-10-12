
class mysql::server::install {
  $password = "password"
  
  package { "mysql-server": 
  	ensure => "5.5.24-0ubuntu0.12.04.1"
  }
    
  phpfpm::extension { "php5-mysql": }

  exec { "Set MySQL server root password":
    subscribe => Package["mysql-server"],
    refreshonly => true,
    unless => "mysqladmin -uroot -p$password status",
    path => "/bin:/usr/bin",
    command => "mysqladmin -uroot password $password",
  }
  
   
}