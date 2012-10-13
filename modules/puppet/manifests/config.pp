/**
 * 
 * Makes sure the puppet agent does not need to be re-run with the --server flag 
 * Sets up reporting
 * 
 */
class puppet::config {
	
	$puppetserver = "kalabox.kalamuna.com"
	
	file { "/etc/puppet/puppet.conf" :
		ensure => present,
		content => template("puppet/puppet.conf.erb"),
		owner => "puppet",
		group => "puppet",
		require => Class["puppet::install"],
		notify => Class["puppet::service"],
	}
}