/**
 * 
 * Installs the puppet agent
 * 
 */
class puppet::install {
    
	package { "puppet" : 
		ensure => present,
	}
	
}