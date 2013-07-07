/**
 *
 * Class that governs the creation of the mysql-server configuration
 *
 */
class mysql::server::config {

	mysql::my { "my.cnf":
	  path => "/etc/mysql/my.cnf",
	  require => File["/etc/kalastack/mysql"],
	  notify => Class["mysql::server::service"],
	}

  file { "/etc/kalastack/mysql":
    ensure  => directory,
    mode    => 777,
    owner   => 501,
    group   => dialout,
    require => [Class["mysql::server::install"], Class["kalabox::build"]],
  }

}
