/**
 * 
 * Makes sure the agent is running
 * 
 */
class puppet::service {
	service { "puppet":
		ensure => running,
		hasstatus => true,
		hasrestart => true,
		enable => true,
		require => Class["puppet::install"],
	}
}