<?php
abstract class AbstractRepo {
	private $db;
	
	protected function __construct() {
		$db_host = 'localhost';
		$db_user = 'root';
		$db_pwd = '';
		$db_name = 'forum2';

		$this->db = new PDO("mysql:host=$db_host;dbname=$db_name;charset=utf8", $db_user, $db_pwd, 
			array(PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION));
	}
	
	public function getDb() {
		return $this->db;
	}
}
?>

