/**
 * 
 * Makes sure the mysql service is running
 * 
 */
class mysql::server::service {
    
  service { "mysql-server":
    ensure      => running,
    name        => "mysql",
    hasstatus   => true,
    hasrestart  => true,
    enable      => true,
    require     => Class["mysql::server::install"],
  }
  
}
