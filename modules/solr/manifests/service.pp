class solr::service {
	service { $solr::params::tomcat:
		ensure => running,
		hasstatus => true,
		hasrestart => true,
		enable => true,
		require => Class["solr::install"],
	}
}