/**
 * 
 * Class that governs the creation of the mysql-server configuration
 * 
 */
class mysql::server::config {
	
	mysql::my { "my.cnf": 
	  path => "/etc/mysql/my.cnf",
	  require => Class["mysql::server::install"],
	  notify => Class["mysql::server::service"],
	}

}