/**
 * 
 * Basic definition to create a database
 * 
 */
define mysql::server::db($username, $password, $host = 'localhost') {
    
  $root_password = $mysql::server::install::password
  
  exec { "create-${name}-db":
    unless => "/usr/bin/mysql -u${username} -p${password} ${name}",
    command => "/usr/bin/mysql -uroot -p${root_password} -e \"create database ${name}; grant all on ${name}.* to ${username}@${host} identified by '$password';\"",
    require => Class['mysql::server::service'],
  }
  
}
