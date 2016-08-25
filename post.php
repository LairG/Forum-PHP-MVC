<?php
   session_start();
   require_once 'model/Post.class.inc';
   require_once 'model/Topic.class.inc';
   require_once 'model/User.class.inc';
   require_once 'orm/PostAffDeleteRepo.class.inc';
   require_once 'orm/PostEditRepo.class.inc';
   require_once 'controller/post.inc';
   require_once 'view/post.inc';
?>