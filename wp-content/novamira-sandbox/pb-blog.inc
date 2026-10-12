<?php
/**
 * PPC BAPPI blog layer: archive (blog, category, tag, search) and single post templates.
 */
if ( ! defined( 'ABSPATH' ) ) { exit; }

define( 'PB_BLOG_PER_PAGE', 9 );

function pb_blog_is_list() {
	return is_home() || is_category() || is_tag() || is_search() || is_author() || is_date();
}

add_filter( 'template_include', function ( $t ) {
	if ( pb_blog_is_list() ) { return __DIR__ . '/pb-tpl-list.php'; }
	if ( is_singular( 'post' ) ) { return __DIR__ . '/pb-tpl-single.php'; }
	return $t;
}, 99 );

/* 3-column grid: 9 posts per page, posts only, latest first */
add_action( 'pre_get_posts', function ( $q ) {
	if ( is_admin() || ! $q->is_main_query() ) { return; }
	if ( $q->is_home() || $q->is_category() || $q->is_tag() || $q->is_search() || $q->is_author() || $q->is_date() ) {
		$q->set( 'posts_per_page', PB_BLOG_PER_PAGE );
		if ( $q->is_search() ) { $q->set( 'post_type', 'post' ); }
	}
} );

function pb_blog_url() {
	$pf = get_option( 'page_for_posts' );
	return $pf ? get_permalink( $pf ) : home_url( '/blog/' );
}

function pb_read_time( $id = null ) {
	$w = str_word_count( wp_strip_all_tags( get_post_field( 'post_content', $id ? $id : get_the_ID() ) ) );
	return max( 1, (int) ceil( $w / 220 ) ) . ' min read';
}

function pb_post_cat( $id = null ) {
	$c = get_the_category( $id ? $id : get_the_ID() );
	return $c ? $c[0] : null;
}

function pb_bic( $n ) {
	$s = array(
		'cal'    => '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" aria-hidden="true"><rect x="3.5" y="5" width="17" height="15.5" rx="2.5"/><path d="M3.5 10h17M8 3v4M16 3v4"/></svg>',
		'clock'  => '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" aria-hidden="true"><circle cx="12" cy="12" r="8.5"/><path d="M12 7.5V12l3 2"/></svg>',
		'search' => '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" aria-hidden="true"><circle cx="11" cy="11" r="7"/><path d="m20 20-3.5-3.5"/></svg>',
		'prev'   => '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true"><path d="M15 6l-6 6 6 6"/></svg>',
		'next'   => '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true"><path d="M9 6l6 6-6 6"/></svg>',
		'copy'   => '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true"><rect x="9" y="9" width="11" height="11" rx="2"/><path d="M5 15V6a2 2 0 0 1 2-2h9"/></svg>',
	);
	return isset( $s[ $n ] ) ? $s[ $n ] : '';
}

/* ---------- Card ---------- */
function pb_post_card() {
	$id    = get_the_ID();
	$url   = get_permalink();
	$title = get_the_title();
	$img   = has_post_thumbnail() ? get_the_post_thumbnail( $id, 'medium_large', array( 'loading' => 'lazy', 'alt' => esc_attr( $title ) ) ) : '<span class="pb-card__ph">' . pb_ic( 'gtm' ) . '</span>';
	$o     = '<article class="pb-card">';
	$o    .= '<a class="pb-card__img" href="' . esc_url( $url ) . '" tabindex="-1" aria-hidden="true">' . $img . '</a>';
	$o    .= '<div class="pb-card__b">';
	$o    .= '<h3 class="pb-card__t"><a href="' . esc_url( $url ) . '">' . esc_html( $title ) . '</a></h3>';
	$o    .= '<time class="pb-card__d" datetime="' . esc_attr( get_the_date( 'c' ) ) . '">' . pb_bic( 'cal' ) . esc_html( get_the_date( 'F j, Y' ) ) . '</time>';
	$o    .= '<p class="pb-card__x">' . esc_html( wp_trim_words( get_the_excerpt(), 22 ) ) . '</p>';
	$o    .= '<a class="pb-card__more" href="' . esc_url( $url ) . '" aria-label="Read more: ' . esc_attr( $title ) . '">Read More <span aria-hidden="true">&raquo;</span></a>';
	return $o . '</div></article>';
}

/* ---------- Pagination: Previous 1 2 3 Next ---------- */
function pb_pagination() {
	global $wp_query;
	$total = (int) $wp_query->max_num_pages;
	if ( $total < 2 ) { return ''; }
	$cur   = max( 1, (int) get_query_var( 'paged' ) );
	$links = paginate_links( array( 'current' => $cur, 'total' => $total, 'mid_size' => 1, 'end_size' => 1, 'prev_next' => false, 'type' => 'array' ) );
	$o     = '<nav class="pb-pag" aria-label="Blog pagination"><ul>';
	$o    .= '<li>' . ( $cur > 1 ? '<a class="pb-pag__nav" href="' . esc_url( get_pagenum_link( $cur - 1 ) ) . '" rel="prev">' . pb_bic( 'prev' ) . 'Previous</a>' : '<span class="pb-pag__nav is-off" aria-disabled="true">' . pb_bic( 'prev' ) . 'Previous</span>' ) . '</li>';
	foreach ( (array) $links as $l ) { $o .= '<li>' . $l . '</li>'; }
	$o .= '<li>' . ( $cur < $total ? '<a class="pb-pag__nav" href="' . esc_url( get_pagenum_link( $cur + 1 ) ) . '" rel="next">Next' . pb_bic( 'next' ) . '</a>' : '<span class="pb-pag__nav is-off" aria-disabled="true">Next' . pb_bic( 'next' ) . '</span>' ) . '</li>';
	return $o . '</ul></nav>';
}

/* ---------- Sidebar ---------- */
function pb_socials() {
	$l = pb_links();
	$o = '<div class="pb-soc">';
	foreach ( array( 'linkedin' => 'LinkedIn', 'youtube' => 'YouTube', 'facebook' => 'Facebook', 'upwork' => 'Upwork', 'fiverr' => 'Fiverr' ) as $k => $n ) {
		$o .= '<a href="' . esc_url( $l[ $k ] ) . '" target="_blank" rel="noopener" aria-label="' . esc_attr( $n ) . '" title="' . esc_attr( $n ) . '">' . pb_ic( $k ) . '</a>';
	}
	return $o . '</div>';
}

function pb_search_box() {
	return '<form class="pb-sbox pb-search" role="search" method="get" action="' . esc_url( home_url( '/' ) ) . '"><label class="screen-reader-text" for="pb-s">Search the blog</label><input id="pb-s" type="search" name="s" value="' . esc_attr( get_search_query() ) . '" placeholder="Find Your Blog..."><input type="hidden" name="post_type" value="post"><button type="submit" aria-label="Search">' . pb_bic( 'search' ) . '</button></form>';
}

function pb_author_card() {
	$photo = wp_get_attachment_image( PB_PHOTO, 'medium', false, array( 'alt' => 'PPC BAPPI, Google Ads and tracking specialist', 'loading' => 'lazy' ) );
	return '<div class="pb-sbox pb-auth"><div class="pb-auth__ph">' . $photo . '</div><h3>PPC BAPPI</h3><p class="pb-auth__role">Google Ads &amp; Tracking Specialist</p><p class="pb-auth__bio">I build and fix Google Ads conversion tracking, GTM containers, GA4 setups and server-side tracking, so the numbers in your ad accounts match what really happens on your site.</p>' . pb_socials() . '<a class="pb-auth__more" href="' . esc_url( home_url( '/about/' ) ) . '">More about me <span aria-hidden="true">&raquo;</span></a></div>';
}

function pb_lm_art() {
	return '<svg class="pb-lm__art" viewBox="0 0 280 120" role="img" aria-label="GTM listener code illustration"><rect x=".5" y=".5" width="279" height="119" rx="12" fill="#06111F" stroke="rgba(148,163,184,.24)"/><path d="M.5 12.5A12 12 0 0 1 12.5.5h255a12 12 0 0 1 12 12V24H.5z" fill="#0B1F33"/><circle cx="14" cy="12" r="3.2" fill="#FF5F57"/><circle cx="25" cy="12" r="3.2" fill="#FEBC2E"/><circle cx="36" cy="12" r="3.2" fill="#28C840"/><text x="52" y="15.5" font-family="ui-monospace,Menlo,monospace" font-size="8.5" fill="#94A3B8">listener.js</text><g font-family="ui-monospace,Menlo,monospace" font-size="9.5"><text x="14" y="44" fill="#64748B">1</text><text x="28" y="44"><tspan fill="#1683FF">window</tspan><tspan fill="#E2E8F0">.addEventListener(</tspan><tspan fill="#FDBA74">\'submit\'</tspan><tspan fill="#E2E8F0">, e =&gt;</tspan></text><text x="14" y="60" fill="#64748B">2</text><text x="40" y="60"><tspan fill="#E2E8F0">dataLayer.</tspan><tspan fill="#00E5A0">push</tspan><tspan fill="#E2E8F0">({</tspan></text><text x="14" y="76" fill="#64748B">3</text><text x="52" y="76"><tspan fill="#93C5FD">event</tspan><tspan fill="#E2E8F0">: </tspan><tspan fill="#FDBA74">\'form_submit\'</tspan></text><text x="14" y="92" fill="#64748B">4</text><text x="40" y="92" fill="#E2E8F0">}));</text></g><g transform="translate(222 70)"><circle r="28" fill="rgba(0,229,160,.1)" stroke="rgba(0,229,160,.45)"/><g transform="translate(-15 -15) scale(.625)">' . preg_replace( '#^<svg[^>]*>|</svg>$#', '', pb_ic( 'gtm' ) ) . '</g></g></svg>';
}

function pb_lead_magnet( $where = 'blog' ) {
	$st    = isset( $_GET['pb_lm'] ) ? sanitize_key( wp_unslash( $_GET['pb_lm'] ) ) : '';
	$alert = '';
	if ( '1' === $st ) { $alert = '<div class="pb-alert ok" role="status">Thanks! Check your inbox, the listener code is on its way.</div>'; }
	if ( 'err' === $st ) { $alert = '<div class="pb-alert err" role="alert">Please enter a valid email address.</div>'; }
	$back = is_singular() ? get_permalink() : home_url( remove_query_arg( array( 'pb_lm', 'pb_sent' ), add_query_arg( array() ) ) );
	$o    = '<div class="pb-sbox pb-lm" id="free-code">' . pb_lm_art() . '<h3>Free GTM Listener Code</h3><p>Get started with your tracking setup.</p>' . $alert;
	$o   .= '<form method="post" action="' . esc_url( admin_url( 'admin-post.php' ) ) . '"><input type="hidden" name="action" value="pb_gtm_code">' . wp_nonce_field( 'pb_gtm_code', 'pb_lm_nonce', true, false );
	$o   .= '<input type="hidden" name="pb_back" value="' . esc_attr( $back ) . '"><input type="hidden" name="pb_where" value="' . esc_attr( $where ) . '">';
	$o   .= '<label class="hp" aria-hidden="true">Leave empty<input type="text" name="pb_hp" tabindex="-1" autocomplete="off"></label>';
	$o   .= '<label class="screen-reader-text" for="pb-lm-email-' . esc_attr( $where ) . '">Email address</label><input id="pb-lm-email-' . esc_attr( $where ) . '" type="email" name="email" required placeholder="Your email address" autocomplete="email">';
	$o   .= '<button class="pb-btn pb-btn--p" type="submit">Get Free Code' . pb_ic( 'arrow' ) . '</button></form><small>No spam. Unsubscribe any time.</small></div>';
	return $o;
}

function pb_handle_gtm_code() {
	$back = isset( $_POST['pb_back'] ) ? esc_url_raw( wp_unslash( $_POST['pb_back'] ) ) : pb_blog_url();
	if ( ! wp_validate_redirect( $back, false ) ) { $back = pb_blog_url(); }
	if ( ! empty( $_POST['pb_hp'] ) ) { wp_safe_redirect( add_query_arg( 'pb_lm', '1', $back ) . '#free-code' ); exit; }
	$ok    = isset( $_POST['pb_lm_nonce'] ) && wp_verify_nonce( sanitize_text_field( wp_unslash( $_POST['pb_lm_nonce'] ) ), 'pb_gtm_code' );
	$email = sanitize_email( wp_unslash( $_POST['email'] ?? '' ) );
	if ( ! $ok || ! is_email( $email ) ) {
		wp_safe_redirect( add_query_arg( 'pb_lm', 'err', $back ) . '#free-code' );
		exit;
	}
	$page = wp_get_referer() ? wp_get_referer() : $back;
	$body = "Email: $email\nRequested: Free GTM Listener Code\nPage: $page\nTime: " . wp_date( 'Y-m-d H:i' ) . ' (' . wp_timezone_string() . ')';
	wp_insert_post( array( 'post_type' => 'pb_lead', 'post_status' => 'private', 'post_title' => 'GTM Listener Code (' . $email . ')', 'post_content' => $body ) );
	wp_mail( 'ppcbappi@gmail.com', 'New Free GTM Listener Code request: ' . $email, $body, array( 'From: PPC BAPPI Website <no-reply@ppcbappi.com>', 'Reply-To: ' . $email ) );
	wp_safe_redirect( add_query_arg( 'pb_lm', '1', $back ) . '#free-code' );
	exit;
}
add_action( 'admin_post_nopriv_pb_gtm_code', 'pb_handle_gtm_code' );
add_action( 'admin_post_pb_gtm_code', 'pb_handle_gtm_code' );

/* ---------- Archive ---------- */
function pb_blog_hero() {
	$eyebrow = 'Blog &amp; resources';
	$title   = 'Tracking, analytics &amp; <span class="pb-grad">Google Ads notes.</span>';
	$lead    = 'Practical guides on GTM, GA4, Google Ads conversion tracking, Meta CAPI and server-side setups, written from real implementation work.';
	if ( is_category() || is_tag() ) {
		$eyebrow = is_category() ? 'Topic' : 'Tag';
		$title   = esc_html( single_term_title( '', false ) );
		$d       = term_description();
		$lead    = $d ? esc_html( wp_strip_all_tags( $d ) ) : 'All articles filed under ' . esc_html( single_term_title( '', false ) ) . '.';
	} elseif ( is_search() ) {
		$eyebrow = 'Search';
		$title   = 'Results for &ldquo;' . esc_html( get_search_query() ) . '&rdquo;';
		$lead    = '';
	} elseif ( is_author() || is_date() ) {
		$title = esc_html( wp_strip_all_tags( get_the_archive_title() ) );
		$lead  = '';
	}
	$crumb = '<nav class="pb-crumbs" aria-label="Breadcrumb"><a href="' . esc_url( home_url( '/' ) ) . '">Home</a><span>/</span>' . ( is_home() ? '<span aria-current="page">Blog</span>' : '<a href="' . esc_url( pb_blog_url() ) . '">Blog</a>' ) . '</nav>';
	$chips = '';
	$cats  = get_categories( array( 'hide_empty' => true, 'exclude' => array( (int) get_option( 'default_category' ) ), 'number' => 8 ) );
	if ( $cats ) {
		$chips = '<nav class="pb-topics" aria-label="Topics"><a class="' . ( is_home() ? 'on' : '' ) . '" href="' . esc_url( pb_blog_url() ) . '">All</a>';
		foreach ( $cats as $c ) { $chips .= '<a class="' . ( is_category( $c->term_id ) ? 'on' : '' ) . '" href="' . esc_url( get_category_link( $c ) ) . '">' . esc_html( $c->name ) . '</a>'; }
		$chips .= '</nav>';
	}
	return '<section class="pb pb-bhero"><div class="pb-wrap pb-bwrap">' . $crumb . '<span class="pb-eyebrow">' . $eyebrow . '</span><h1>' . $title . '</h1>' . ( $lead ? '<p class="pb-lead">' . $lead . '</p>' : '' ) . $chips . '</div></section>';
}

function pb_blog_render_list() {
	$l = pb_links();
	echo '<div class="pb-bpage">' . pb_blog_hero() . '<section class="pb pb-bl"><div class="pb-wrap pb-bwrap"><div class="pb-bl__grid"><div class="pb-bl__main">'; // phpcs:ignore
	if ( have_posts() ) {
		echo '<div class="pb-cards">';
		while ( have_posts() ) { the_post(); echo pb_post_card(); } // phpcs:ignore
		echo '</div>' . pb_pagination(); // phpcs:ignore
	} elseif ( is_search() ) {
		echo '<div class="pb-blog-empty"><h2>No articles matched that search.</h2><p>Try a different keyword, or ask me directly about your tracking problem.</p><div class="pb-hero__btns">' . pb_btn( 'Get a Free Tracking Audit', $l['audit'] ) . '</div></div>'; // phpcs:ignore
	} else {
		echo '<div class="pb-blog-empty"><h2>The first articles are being written.</h2><p>Until they are published, my YouTube channel has practical tutorials on Google Ads, GTM, GA4 and conversion tracking.</p><div class="pb-hero__btns">' . pb_btn( 'Visit My YouTube Channel', $l['yt_home'] ) . pb_btn( 'Get a Free Tracking Audit', $l['audit'], 'o' ) . '</div></div>'; // phpcs:ignore
	}
	echo '</div><aside class="pb-side" aria-label="Blog sidebar">' . pb_search_box() . pb_author_card() . pb_lead_magnet( 'blog' ) . '</aside></div></div></section></div>'; // phpcs:ignore
}

/* ---------- Single post ---------- */
function pb_toc_content( $html, &$toc ) {
	$toc  = array();
	$used = array();
	$html = preg_replace_callback( '#<h([23])([^>]*)>(.*?)</h\1>#is', function ( $m ) use ( &$toc, &$used ) {
		$text = trim( wp_strip_all_tags( $m[3] ) );
		if ( '' === $text ) { return $m[0]; }
		if ( preg_match( '#\sid=["\']([^"\']+)#', $m[2], $idm ) ) {
			$id    = $idm[1];
			$attrs = $m[2];
		} else {
			$id = sanitize_title( $text );
			if ( ! $id ) { $id = 'section'; }
			$base = $id; $n = 2;
			while ( isset( $used[ $id ] ) ) { $id = $base . '-' . $n++; }
			$attrs = $m[2] . ' id="' . esc_attr( $id ) . '"';
		}
		$used[ $id ] = 1;
		$toc[]       = array( (int) $m[1], $id, $text );
		return '<h' . $m[1] . $attrs . '>' . $m[3] . '</h' . $m[1] . '>';
	}, $html );
	return $html;
}

function pb_toc_html( $toc, $cls ) {
	if ( count( $toc ) < 3 ) { return ''; }
	$o = '<ol>';
	foreach ( $toc as $t ) { $o .= '<li class="l' . $t[0] . '"><a href="#' . esc_attr( $t[1] ) . '">' . esc_html( $t[2] ) . '</a></li>'; }
	$o .= '</ol>';
	if ( 'm' === $cls ) { return '<details class="pb-toc pb-toc--m"><summary>Table of contents</summary>' . $o . '</details>'; }
	return '<nav class="pb-sbox pb-toc pb-toc--d" aria-label="Table of contents"><h4>Table of contents</h4>' . $o . '</nav>';
}

/* FAQ: the <details> blocks that follow an "FAQ" / "Frequently Asked Questions" heading */
function pb_faq_items( $html ) {
	if ( ! preg_match( '#<h[23][^>]*>\s*(?:faqs?|frequently asked questions)\b.*?</h[23]>(.*)$#is', $html, $m ) ) { return array(); }
	$rest = preg_split( '#<h2[\s>]#i', $m[1] )[0];
	preg_match_all( '#<details[^>]*>\s*<summary[^>]*>(.*?)</summary>(.*?)</details>#is', $rest, $d, PREG_SET_ORDER );
	$out = array();
	foreach ( $d as $x ) {
		$q = trim( wp_strip_all_tags( $x[1] ) );
		$a = trim( wp_strip_all_tags( $x[2] ) );
		if ( $q && $a ) { $out[] = array( '@type' => 'Question', 'name' => $q, 'acceptedAnswer' => array( '@type' => 'Answer', 'text' => $a ) ); }
	}
	return $out;
}

function pb_share() {
	$u = rawurlencode( get_permalink() );
	$t = rawurlencode( get_the_title() );
	return '<div class="pb-share"><span>Share</span>'
		. '<a href="https://www.linkedin.com/sharing/share-offsite/?url=' . $u . '" target="_blank" rel="noopener" aria-label="Share on LinkedIn">' . pb_ic( 'linkedin' ) . '</a>'
		. '<a href="https://www.facebook.com/sharer/sharer.php?u=' . $u . '" target="_blank" rel="noopener" aria-label="Share on Facebook">' . pb_ic( 'facebook' ) . '</a>'
		. '<a href="https://twitter.com/intent/tweet?url=' . $u . '&amp;text=' . $t . '" target="_blank" rel="noopener" aria-label="Share on X"><svg viewBox="0 0 24 24" fill="currentColor"><path d="M17.8 3h3.1l-6.8 7.7L22 21h-6.2l-4.9-6.4L5.3 21H2.2l7.2-8.3L1.8 3h6.4l4.4 5.8L17.8 3zm-1.1 16.2h1.7L7.4 4.7H5.6l11.1 14.5z"/></svg></a>'
		. '<button type="button" class="pb-copy" data-url="' . esc_attr( get_permalink() ) . '" aria-label="Copy link"><svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round"><path d="M10 14a5 5 0 0 0 7 0l3-3a5 5 0 0 0-7-7l-1 1"/><path d="M14 10a5 5 0 0 0-7 0l-3 3a5 5 0 0 0 7 7l1-1"/></svg></button></div>';
}

function pb_related( $id ) {
	$cat = pb_post_cat( $id );
	$q   = new WP_Query( array( 'post_type' => 'post', 'posts_per_page' => 3, 'post__not_in' => array( $id ), 'ignore_sticky_posts' => true, 'no_found_rows' => true, 'cat' => $cat ? $cat->term_id : 0 ) );
	if ( ! $q->have_posts() && $cat ) {
		$q = new WP_Query( array( 'post_type' => 'post', 'posts_per_page' => 3, 'post__not_in' => array( $id ), 'ignore_sticky_posts' => true, 'no_found_rows' => true ) );
	}
	if ( ! $q->have_posts() ) { return ''; }
	$o = '<section class="pb pb-rel"><div class="pb-wrap pb-bwrap"><div class="pb-rel__h"><div><span class="pb-eyebrow">Keep reading</span><h2>Related Articles</h2></div><a class="pb-card__more" href="' . esc_url( pb_blog_url() ) . '">All articles <span aria-hidden="true">&raquo;</span></a></div><div class="pb-cards">';
	while ( $q->have_posts() ) { $q->the_post(); $o .= pb_post_card(); }
	wp_reset_postdata();
	return $o . '</div></div></section>';
}

function pb_blog_render_single() {
	while ( have_posts() ) {
		the_post();
		$id      = get_the_ID();
		$cat     = pb_post_cat();
		$toc     = array();
		$content = pb_toc_content( apply_filters( 'the_content', get_the_content() ), $toc );
		$faq     = pb_faq_items( $content );
		$upd     = get_the_modified_date( 'U' ) - get_the_date( 'U' ) > DAY_IN_SECONDS ? '<span>Updated ' . esc_html( get_the_modified_date( 'M j, Y' ) ) . '</span>' : '';
		$avatar  = wp_get_attachment_image( PB_PHOTO, 'thumbnail', false, array( 'alt' => '', 'class' => 'pb-av' ) );

		$o  = '<div class="pb-bpage pb-single"><section class="pb pb-shero"><div class="pb-wrap pb-bwrap"><div class="pb-shero__in">';
		$o .= '<nav class="pb-crumbs" aria-label="Breadcrumb"><a href="' . esc_url( home_url( '/' ) ) . '">Home</a><span>/</span><a href="' . esc_url( pb_blog_url() ) . '">Blog</a>' . ( $cat ? '<span>/</span><a href="' . esc_url( get_category_link( $cat ) ) . '">' . esc_html( $cat->name ) . '</a>' : '' ) . '</nav>';
		$o .= ( $cat ? '<a class="pb-cat" href="' . esc_url( get_category_link( $cat ) ) . '">' . esc_html( $cat->name ) . '</a>' : '' );
		$o .= '<h1>' . esc_html( get_the_title() ) . '</h1>';
		$o .= '<div class="pb-smeta">' . $avatar . '<span>By <b>PPC BAPPI</b></span><span>' . pb_bic( 'cal' ) . '<time datetime="' . esc_attr( get_the_date( 'c' ) ) . '">' . esc_html( get_the_date( 'F j, Y' ) ) . '</time></span>' . $upd . '<span>' . pb_bic( 'clock' ) . esc_html( pb_read_time() ) . '</span></div>';
		$o .= '</div></div></section>';

		$o .= '<section class="pb pb-bl pb-bl--s"><div class="pb-wrap pb-bwrap"><div class="pb-bl__grid"><article class="pb-art">';
		if ( has_post_thumbnail() ) { $o .= '<figure class="pb-art__img">' . get_the_post_thumbnail( $id, 'large', array( 'alt' => esc_attr( get_the_title() ), 'fetchpriority' => 'high' ) ) . '</figure>'; }
		$o .= '<div class="pb-art__card">' . pb_toc_html( $toc, 'm' );
		$o .= '<div class="pb-prose">' . $content . '</div>';
		$tags = get_the_tags();
		$o   .= '<div class="pb-art__f">';
		if ( $tags ) {
			$o .= '<div class="pb-tags">';
			foreach ( $tags as $tg ) { $o .= '<a href="' . esc_url( get_tag_link( $tg ) ) . '">#' . esc_html( $tg->name ) . '</a>'; }
			$o .= '</div>';
		}
		$o .= pb_share() . '</div></div>';
		$o .= '<div class="pb-abox">' . wp_get_attachment_image( PB_PHOTO, 'medium', false, array( 'alt' => 'PPC BAPPI', 'loading' => 'lazy' ) ) . '<div><span class="pb-eyebrow">Written by</span><h3>PPC BAPPI</h3><p>Google Ads and tracking specialist. I help businesses build reliable GTM, GA4, Google Ads, Meta CAPI and server-side tracking so they can see what is actually converting.</p>' . pb_socials() . '</div></div>';
		$o .= '</article><aside class="pb-side pb-side--sticky" aria-label="Article sidebar">' . pb_toc_html( $toc, 'd' ) . pb_author_card() . pb_lead_magnet( 'post' ) . '</aside></div></div></section>';
		$o .= pb_related( $id );
		$o .= '<div class="pb-scta">' . do_shortcode( '[pb_cta]' ) . '</div>';
		$o .= '</div>';

		$ld = array(
			'@context'         => 'https://schema.org',
			'@type'            => 'BlogPosting',
			'headline'         => get_the_title(),
			'datePublished'    => get_the_date( 'c' ),
			'dateModified'     => get_the_modified_date( 'c' ),
			'mainEntityOfPage' => get_permalink(),
			'author'           => array( '@type' => 'Person', 'name' => 'PPC BAPPI', 'url' => home_url( '/about/' ) ),
			'publisher'        => array( '@type' => 'Person', 'name' => 'PPC BAPPI', 'url' => home_url( '/' ) ),
			'description'      => wp_trim_words( get_the_excerpt(), 30, '' ),
		);
		if ( has_post_thumbnail() ) { $ld['image'] = get_the_post_thumbnail_url( $id, 'large' ); }
		$o .= '<script type="application/ld+json">' . wp_json_encode( $ld, JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE ) . '</script>';
		if ( $faq ) {
			$o .= '<script type="application/ld+json">' . wp_json_encode( array( '@context' => 'https://schema.org', '@type' => 'FAQPage', 'mainEntity' => $faq ), JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE ) . '</script>';
		}
		$o .= '<script>(function(){var l=document.querySelectorAll(".pb-toc--d a");if(!l.length||!("IntersectionObserver" in window))return;var m={};l.forEach(function(a){m[a.getAttribute("href").slice(1)]=a});var io=new IntersectionObserver(function(es){es.forEach(function(e){if(e.isIntersecting){l.forEach(function(x){x.classList.remove("on")});var a=m[e.target.id];a&&a.classList.add("on")}})},{rootMargin:"-110px 0px -70% 0px"});Object.keys(m).forEach(function(id){var h=document.getElementById(id);h&&io.observe(h)})})();</script>';
		$o .= '<script>(function(){document.querySelectorAll(".pb-prose pre").forEach(function(p){var w=document.createElement("div");w.className="pb-code";p.parentNode.insertBefore(w,p);w.appendChild(p);var b=document.createElement("button");b.type="button";b.className="pb-code__copy";b.textContent="Copy";w.appendChild(b)});document.addEventListener("click",function(e){var c=e.target.closest(".pb-code__copy");if(c){var t=c.parentNode.querySelector("pre").innerText;navigator.clipboard&&navigator.clipboard.writeText(t);c.textContent="Copied";setTimeout(function(){c.textContent="Copy"},1600);return}var b=e.target.closest(".pb-copy");if(!b)return;navigator.clipboard&&navigator.clipboard.writeText(b.dataset.url);b.classList.add("done");setTimeout(function(){b.classList.remove("done")},1600)})})();</script>';
		echo $o; // phpcs:ignore
	}
}
