
class network::config {
	
	file { "/etc/hosts" :
		ensure => present,
		content => template("network/hosts.erb"),
		owner => "root",
		group => "root",
	}
}