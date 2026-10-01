<?php
if ( ! defined( 'ABSPATH' ) || ! did_action( 'template_redirect' ) ) { return; }
get_header();
pb_blog_render_single();
get_footer();
