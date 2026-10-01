<?php
/**
 * PPC BAPPI site layer: header, footer, shared sections (shortcodes), contact form, leads.
 */
if ( ! defined( 'ABSPATH' ) ) { exit; }

define( 'PB_VER', '1.0.0' );
define( 'PB_PHOTO', 26 );

function pb_links() {
	return array(
		'fiverr'    => 'https://www.fiverr.com/ppc_bappi',
		'upwork'    => 'https://www.upwork.com/freelancers/ppcbappi',
		'skilluper' => 'https://skilluper.com/instructors/',
		'youtube'   => 'https://www.youtube.com/channel/UCGoDnvlTeg2r2rMYUY9RlGg/about',
		'yt_home'   => 'https://www.youtube.com/channel/UCGoDnvlTeg2r2rMYUY9RlGg',
		'linkedin'  => 'https://www.linkedin.com/in/labib-ahammed-bappi?originalSubdomain=bd',
		'facebook'  => 'https://web.facebook.com/ppcbappi/about/',
		'book'      => home_url( '/book-a-call/' ),
		'audit'     => home_url( '/contact/?service=tracking-audit#contact' ),
		'contact'   => home_url( '/contact/#contact' ),
	);
}

function pb_services() {
	return array(
		'google-ads-tracking'  => array( 'Google Ads Conversion Tracking', 'Purchases, leads, calls and form submits recorded correctly, with Enhanced Conversions and clean conversion actions.', 'gads' ),
		'google-tag-manager'   => array( 'Google Tag Manager', 'A tidy container with clear naming, a proper dataLayer and tags that fire only when they should.', 'gtm' ),
		'ga4-analytics'        => array( 'Google Analytics 4', 'GA4 setup or repair: key events, custom dimensions, cross-domain and reporting you can actually read.', 'ga4' ),
		'server-side-tracking' => array( 'Server-Side Tracking', 'A GTM server container on your own subdomain for first-party data and more durable measurement.', 'server' ),
		'meta-conversion-api'  => array( 'Meta Conversion API', 'Meta Pixel plus Conversions API with proper deduplication and stronger event matching.', 'meta' ),
		'ecommerce-tracking'   => array( 'Ecommerce Tracking', 'Full funnel events on Shopify and WooCommerce, from product view to purchase, with correct values.', 'cart' ),
	);
}

/* ---------- Icons ---------- */
function pb_ic( $n ) {
	$s = array(
		'arrow'   => '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><path d="M5 12h14M13 6l6 6-6 6"/></svg>',
		'chev'    => '<svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.4" stroke-linecap="round"><path d="m6 9 6 6 6-6"/></svg>',
		'check'   => '<svg viewBox="0 0 24 24" fill="none" stroke="#00E5A0" stroke-width="3" stroke-linecap="round" stroke-linejoin="round"><path d="m5 12 5 5 9-10"/></svg>',
		'checkc'  => '<svg viewBox="0 0 24 24" fill="none"><circle cx="12" cy="12" r="10" fill="rgba(0,229,160,.14)"/><path d="m7.5 12.2 3 3 6-6.4" stroke="#00E5A0" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"/></svg>',
		'gads'    => '<svg viewBox="0 0 48 48"><path fill="#FBBC04" d="M4.6 34.6 17.3 12.6a6.3 6.3 0 0 1 10.9 6.3L15.5 40.9a6.3 6.3 0 1 1-10.9-6.3z"/><path fill="#4285F4" d="M43.4 34.6 30.7 12.6a6.3 6.3 0 0 0-10.9 6.3l12.7 22a6.3 6.3 0 0 0 10.9-6.3z"/><circle cx="10" cy="37.8" r="6.3" fill="#34A853"/></svg>',
		'gtm'     => '<svg viewBox="0 0 48 48"><path fill="#8AB4F8" d="M27.3 45.2 19.7 37.8l16.1-16.4 7.8 7.6z"/><path fill="#4285F4" d="M27.4 10.3 19.8 2.8 3 19.6a4.2 4.2 0 0 0 0 5.9l16.8 16.8 7.4-7.6L15.3 22.6z"/><path fill="#8AB4F8" d="M45 19.7 28.3 3a4.2 4.2 0 0 0-5.9 5.9l16.7 16.7a4.2 4.2 0 0 0 5.9-5.9z"/><circle cx="23.4" cy="41.6" r="4.2" fill="#246FDB"/></svg>',
		'ga4'     => '<svg viewBox="0 0 48 48"><rect x="31" y="4" width="11" height="40" rx="5.5" fill="#F9AB00"/><path fill="#E37400" d="M18.5 19.5h0a5.5 5.5 0 0 1 5.5 5.5v13.5a5.5 5.5 0 0 1-11 0V25a5.5 5.5 0 0 1 5.5-5.5z"/><circle cx="8.5" cy="38.5" r="5.5" fill="#E37400"/></svg>',
		'meta'    => '<svg viewBox="0 0 48 48"><path fill="none" stroke="#0A7CFF" stroke-width="5" stroke-linecap="round" d="M9 33c-3.5 0-5-3-5-7.5C4 18 8 12 12.5 12c4 0 7 4.5 11.5 12s7.5 12 11.5 12c3.5 0 5.5-3 5.5-8 0-7.5-3.5-14-8.5-14-4.5 0-8 6-11.5 12S12.5 33 9 33z"/></svg>',
		'server'  => '<svg viewBox="0 0 24 24" fill="none" stroke="#1683FF" stroke-width="1.8"><rect x="3" y="3.5" width="18" height="7" rx="2" fill="rgba(22,131,255,.15)"/><rect x="3" y="13.5" width="18" height="7" rx="2" fill="rgba(0,229,160,.12)" stroke="#00E5A0"/><circle cx="7" cy="7" r="1" fill="#1683FF"/><circle cx="7" cy="17" r="1" fill="#00E5A0"/><path d="M11 7h6M11 17h6"/></svg>',
		'shield'  => '<svg viewBox="0 0 24 24" fill="none" stroke="#00E5A0" stroke-width="1.8" stroke-linejoin="round"><path d="M12 2.8 4.5 5.8v5.6c0 4.6 3.1 8.6 7.5 9.8 4.4-1.2 7.5-5.2 7.5-9.8V5.8z" fill="rgba(0,229,160,.12)"/><path d="m8.7 12 2.3 2.3 4.4-4.6" stroke-linecap="round"/></svg>',
		'cart'    => '<svg viewBox="0 0 24 24" fill="none" stroke="#00E5A0" stroke-width="1.8" stroke-linecap="round" stroke-linejoin="round"><path d="M3 4h2.2l2.3 11h10.8l2-8H6.3" fill="rgba(0,229,160,.1)"/><circle cx="9.5" cy="19.5" r="1.5"/><circle cx="17" cy="19.5" r="1.5"/></svg>',
		'fiverr'  => '<svg viewBox="0 0 24 24"><rect width="24" height="24" rx="6" fill="#1DBF73"/><path fill="#fff" d="M14.6 7.3h-2.1c-1.6 0-2.5.9-2.5 2.4v.5H8.4v1.9H10V18h2v-5.9h2.6V18h2v-7.8h-4.6v-.4c0-.5.3-.7.8-.7h1.8z"/></svg>',
		'upwork'  => '<svg viewBox="0 0 24 24"><rect width="24" height="24" rx="6" fill="#14A800"/><path fill="#fff" d="M15.8 8.4c-1.9 0-3.1 1.3-3.6 3-.7-1.1-1.3-2.3-1.6-3.4H8.7v4.6c0 .9-.7 1.6-1.6 1.6S5.5 13.5 5.5 12.6V8H3.6v4.6c0 1.9 1.6 3.5 3.5 3.5s3.5-1.6 3.5-3.5v-.8c.3.7.8 1.4 1.2 2l-.9 4.2h1.9l.6-3c.6.4 1.4.6 2.3.6a3.6 3.6 0 0 0 0-7.2zm0 5.3c-.8 0-1.6-.4-2.3-.9l.2-.8c.2-1 .8-1.9 2.1-1.9a1.8 1.8 0 0 1 0 3.6z"/></svg>',
		'skilluper'=> '<svg viewBox="0 0 24 24"><rect width="24" height="24" rx="6" fill="#7C3AED"/><path fill="none" stroke="#fff" stroke-width="1.8" stroke-linejoin="round" d="M12 5.5 4.5 9 12 12.5 19.5 9zM7.5 10.5v4c0 1 2 2.5 4.5 2.5s4.5-1.5 4.5-2.5v-4"/></svg>',
		'youtube' => '<svg viewBox="0 0 24 24"><rect width="24" height="24" rx="6" fill="#FF0033"/><path fill="#fff" d="m10 8.6 5.5 3.4-5.5 3.4z"/></svg>',
		'linkedin'=> '<svg viewBox="0 0 24 24"><rect width="24" height="24" rx="6" fill="#0A66C2"/><path fill="#fff" d="M7.2 9.8h2.2V17H7.2zm1.1-3.5a1.3 1.3 0 1 1 0 2.6 1.3 1.3 0 0 1 0-2.6zm2.9 3.5h2.1v1c.3-.6 1-1.2 2.2-1.2 2.3 0 2.7 1.5 2.7 3.5V17h-2.2v-3.4c0-.8 0-1.9-1.2-1.9s-1.4.9-1.4 1.8V17h-2.2z"/></svg>',
		'facebook'=> '<svg viewBox="0 0 24 24"><rect width="24" height="24" rx="6" fill="#1877F2"/><path fill="#fff" d="M13.4 19v-6h2l.3-2.4h-2.3V9.2c0-.7.2-1.2 1.2-1.2h1.2V5.9c-.2 0-1-.1-1.8-.1-1.8 0-3 1.1-3 3.1v1.8H9V13h2v6z"/></svg>',
		'play'    => '<svg viewBox="0 0 24 24"><path fill="#fff" d="M7 4.5v15l13-7.5z"/></svg>',
		'pin'     => '<svg viewBox="0 0 24 24" fill="none" stroke="#00E5A0" stroke-width="1.8"><path d="M12 21s7-6.2 7-11.5A7 7 0 0 0 5 9.5C5 14.8 12 21 12 21z"/><circle cx="12" cy="9.5" r="2.5"/></svg>',
		'globe'   => '<svg viewBox="0 0 24 24" fill="none" stroke="#00E5A0" stroke-width="1.8"><circle cx="12" cy="12" r="9"/><path d="M3 12h18M12 3c2.5 2.7 3.7 5.7 3.7 9s-1.2 6.3-3.7 9c-2.5-2.7-3.7-5.7-3.7-9S9.5 5.7 12 3z"/></svg>',
		'cal'     => '<svg viewBox="0 0 24 24" fill="none" stroke="#00E5A0" stroke-width="1.8" stroke-linecap="round"><rect x="3.5" y="5" width="17" height="15.5" rx="2.5"/><path d="M3.5 10h17M8 3v4M16 3v4"/></svg>',
		'mail'    => '<svg viewBox="0 0 24 24" fill="none" stroke="#00E5A0" stroke-width="1.8"><rect x="3" y="5" width="18" height="14" rx="2.5"/><path d="m4 7 8 6 8-6"/></svg>',
	);
	return isset( $s[ $n ] ) ? $s[ $n ] : '';
}

function pb_btn( $label, $url, $variant = 'p', $extra = '' ) {
	return '<a class="pb-btn pb-btn--' . esc_attr( $variant ) . ' ' . esc_attr( $extra ) . '" href="' . esc_url( $url ) . '">' . esc_html( $label ) . pb_ic( 'arrow' ) . '</a>';
}

/* ---------- Assets ---------- */
add_action( 'wp_enqueue_scripts', function () {
	wp_enqueue_style( 'pb-fonts', 'https://fonts.googleapis.com/css2?family=Sora:wght@600;700;800&family=DM+Sans:opsz,wght@9..40,400;9..40,500;9..40,700&family=Caveat:wght@600&display=swap', array(), null );
	$css = WP_CONTENT_DIR . '/uploads/pb/pb-site.css';
	$ver = file_exists( $css ) ? filemtime( $css ) : PB_VER;
	wp_enqueue_style( 'pb-site', content_url( '/uploads/pb/pb-site.css' ), array(), $ver );
}, 99 );

add_action( 'wp_head', function () {
	echo '<link rel="preconnect" href="https://fonts.googleapis.com"><link rel="preconnect" href="https://fonts.gstatic.com" crossorigin><meta name="theme-color" content="#020B16">';
}, 1 );

add_filter( 'body_class', function ( $c ) { $c[] = 'pb-site'; return $c; } );

/* Astra: full width, no sidebar, replace header & footer */
add_filter( 'astra_page_layout', function () { return 'no-sidebar'; } );
add_filter( 'astra_get_content_layout', function ( $l ) { return is_page() ? 'page-builder' : $l; } );
add_action( 'wp', function () {
	remove_action( 'astra_header', 'astra_header_markup' );
	remove_action( 'astra_footer', 'astra_footer_markup' );
	add_action( 'astra_header', 'pb_header' );
	add_action( 'astra_footer', 'pb_footer' );
} );

/* Run shortcodes inside Elementor HTML widgets */
add_filter( 'elementor/widget/render_content', function ( $content, $widget ) {
	if ( 'html' === $widget->get_name() && false !== strpos( $content, '[pb_' ) ) {
		return do_shortcode( $content );
	}
	return $content;
}, 10, 2 );

function pb_is( $slug ) {
	if ( 'home' === $slug ) { return is_front_page(); }
	if ( 'blog' === $slug ) { return is_home() || is_singular( 'post' ) || is_category() || is_tag(); }
	if ( is_page() ) {
		$p = get_post();
		if ( $p->post_name === $slug ) { return true; }
		if ( 'services' === $slug && $p->post_parent && 'services' === get_post_field( 'post_name', $p->post_parent ) ) { return true; }
	}
	return false;
}

function pb_header() {
	$l   = pb_links();
	$nav = array(
		'home'     => array( 'Home', home_url( '/' ) ),
		'about'    => array( 'About', home_url( '/about/' ) ),
		'services' => array( 'Services', home_url( '/services/' ) ),
		'work'     => array( 'Work', home_url( '/work/' ) ),
		'blog'     => array( 'Blog', home_url( '/blog/' ) ),
		'contact'  => array( 'Contact', home_url( '/contact/' ) ),
	);
	?>
	<header class="pb-hdr pb" id="pbHdr">
		<div class="pb-wrap">
			<div class="pb-hdr__in">
				<a class="pb-logo" href="https://ppcbappi.com/" aria-label="PPC BAPPI home">PPC <span>BAPPI</span></a>
				<nav aria-label="Main"><ul class="pb-nav">
				<?php foreach ( $nav as $k => $n ) : ?>
					<li class="<?php echo pb_is( $k ) ? 'is-active' : ''; ?>">
						<a href="<?php echo esc_url( $n[1] ); ?>"><?php echo esc_html( $n[0] ); ?><?php echo 'services' === $k ? pb_ic( 'chev' ) : ''; ?></a>
						<?php if ( 'services' === $k ) : ?>
						<ul class="pb-dd">
							<?php foreach ( pb_services() as $slug => $s ) : ?>
							<li><a href="<?php echo esc_url( home_url( '/services/' . $slug . '/' ) ); ?>"><?php echo esc_html( $s[0] ); ?></a></li>
							<?php endforeach; ?>
						</ul>
						<?php endif; ?>
					</li>
				<?php endforeach; ?>
				</ul></nav>
				<div class="pb-hdr__r">
					<?php echo pb_btn( 'Book a Call', $l['book'], 'p', 'pb-btn--sm' ); ?>
					<button class="pb-burger" type="button" aria-label="Open menu" aria-expanded="false" aria-controls="pbMnav"><span></span></button>
				</div>
			</div>
			<div class="pb-mnav" id="pbMnav">
				<ul>
				<?php foreach ( $nav as $k => $n ) : ?>
					<li><a href="<?php echo esc_url( $n[1] ); ?>"><?php echo esc_html( $n[0] ); ?></a></li>
					<?php if ( 'services' === $k ) : foreach ( pb_services() as $slug => $s ) : ?>
					<li class="sub"><a href="<?php echo esc_url( home_url( '/services/' . $slug . '/' ) ); ?>"><?php echo esc_html( $s[0] ); ?></a></li>
					<?php endforeach; endif; ?>
				<?php endforeach; ?>
				</ul>
				<?php echo pb_btn( 'Book a Call', $l['book'] ); ?>
			</div>
		</div>
	</header>
	<?php
}

function pb_footer() {
	$l = pb_links();
	?>
	<footer class="pb-ftr pb">
		<div class="pb-wrap">
			<div class="pb-ftr__grid">
				<div class="pb-ftr__brand">
					<a class="pb-logo" href="https://ppcbappi.com/">PPC <span>BAPPI</span></a>
					<div class="t">Google Ads &amp; Tracking Specialist</div>
					<p>I help businesses build reliable tracking with Google Ads, GTM, GA4, Meta Conversion API and server-side tagging.</p>
				</div>
				<div>
					<h4>Quick Links</h4>
					<ul>
						<li><a href="<?php echo esc_url( home_url( '/' ) ); ?>">Home</a></li>
						<li><a href="<?php echo esc_url( home_url( '/about/' ) ); ?>">About</a></li>
						<li><a href="<?php echo esc_url( home_url( '/work/' ) ); ?>">Work</a></li>
						<li><a href="<?php echo esc_url( home_url( '/blog/' ) ); ?>">Blog</a></li>
						<li><a href="<?php echo esc_url( home_url( '/contact/' ) ); ?>">Contact</a></li>
					</ul>
				</div>
				<div>
					<h4>Services</h4>
					<ul>
						<?php foreach ( pb_services() as $slug => $s ) : ?>
						<li><a href="<?php echo esc_url( home_url( '/services/' . $slug . '/' ) ); ?>"><?php echo esc_html( $s[0] ); ?></a></li>
						<?php endforeach; ?>
					</ul>
				</div>
				<div>
					<h4>Follow Me</h4>
					<ul>
						<li><a href="<?php echo esc_url( $l['fiverr'] ); ?>" target="_blank" rel="noopener">Fiverr</a></li>
						<li><a href="<?php echo esc_url( $l['upwork'] ); ?>" target="_blank" rel="noopener">Upwork</a></li>
						<li><a href="<?php echo esc_url( $l['skilluper'] ); ?>" target="_blank" rel="noopener">Skilluper</a></li>
						<li><a href="<?php echo esc_url( $l['yt_home'] ); ?>" target="_blank" rel="noopener">YouTube</a></li>
						<li><a href="<?php echo esc_url( $l['linkedin'] ); ?>" target="_blank" rel="noopener">LinkedIn</a></li>
						<li><a href="<?php echo esc_url( $l['facebook'] ); ?>" target="_blank" rel="noopener">Facebook</a></li>
					</ul>
				</div>
				<div class="pb-ftr__cta">
					<h4>Book a Call</h4>
					<p>Let's talk through your tracking setup and what you want to measure.</p>
					<?php echo pb_btn( 'Book a Call', $l['book'], 'p', 'pb-btn--sm' ); ?>
				</div>
			</div>
			<div class="pb-ftr__bot">
				<span>&copy; <?php echo esc_html( gmdate( 'Y' ) ); ?> PPC BAPPI. All rights reserved.</span>
				<span>Based in Bangladesh. Working with clients worldwide.</span>
			</div>
		</div>
	</footer>
	<script>
	(function(){var h=document.getElementById('pbHdr');if(!h)return;var f=function(){h.classList.toggle('is-scrolled',window.scrollY>20)};f();window.addEventListener('scroll',f,{passive:true});
	var b=h.querySelector('.pb-burger');b&&b.addEventListener('click',function(){var o=h.classList.toggle('is-open');b.setAttribute('aria-expanded',o?'true':'false')});
	h.querySelectorAll('.pb-mnav a').forEach(function(a){a.addEventListener('click',function(){h.classList.remove('is-open')})});
	var s=new URLSearchParams(location.search).get('service');if(s){var sel=document.querySelector('.pb-form select[name=service]');if(sel){for(var i=0;i<sel.options.length;i++){if(sel.options[i].value===s){sel.selectedIndex=i}}}}})();
	</script>
	<?php
}

/* ---------- Shared sections ---------- */
function pb_sec_head( $eyebrow, $title, $sub = '', $right = '' ) {
	$h  = '<div class="pb-head"><div><span class="pb-eyebrow">' . esc_html( $eyebrow ) . '</span><h2 class="pb-h2">' . $title . '</h2>';
	$h .= $sub ? '<p class="pb-lead">' . esc_html( $sub ) . '</p>' : '';
	$h .= '</div>' . $right . '</div>';
	return $h;
}

add_shortcode( 'pb_services_grid', function ( $a ) {
	$a = shortcode_atts( array( 'head' => 'yes' ), $a );
	$o = '<section class="pb pb-sec pb-srv" id="services"><div class="pb-wrap">';
	if ( 'yes' === $a['head'] ) {
		$o .= pb_sec_head( 'What I do', 'My Services', 'Complete tracking solutions to help businesses get accurate data and better marketing results.', pb_btn( 'View All Services', home_url( '/services/' ), 'o', 'pb-btn--sm' ) );
	}
	$o .= '<div class="pb-srv__grid">';
	$i  = 0;
	foreach ( pb_services() as $slug => $s ) {
		$i++;
		$u  = home_url( '/services/' . $slug . '/' );
		$o .= '<article class="pb-sc"><span class="pb-sc__n">' . sprintf( '%02d', $i ) . '</span><div class="pb-sc__ic">' . pb_ic( $s[2] ) . '</div><div class="pb-sc__b"><h3><a href="' . esc_url( $u ) . '">' . esc_html( $s[0] ) . '</a></h3><p>' . esc_html( $s[1] ) . '</p><a class="pb-link" href="' . esc_url( $u ) . '" aria-label="Learn more about ' . esc_attr( $s[0] ) . '">Learn More' . pb_ic( 'arrow' ) . '</a></div></article>';
	}
	return $o . '</div></div></section>';
} );

function pb_cases() {
	return array(
		array(
			'id'    => 'ecommerce-tracking',
			'kind'  => 'Ecommerce brand, UK',
			'title' => 'Ecommerce Tracking Setup',
			'desc'  => 'GA4 ecommerce events, Google Ads purchase conversions and Meta events set up through GTM, so every order reaches each platform with the right value.',
			'tags'  => array( 'GA4', 'GTM', 'Google Ads', 'Meta CAPI' ),
			'win'   => array( 'GA4 · DebugView', array( array( 'view_item', 'Received' ), array( 'add_to_cart', 'Received' ), array( 'begin_checkout', 'Received' ), array( 'purchase', 'Received' ) ) ),
			'more'  => array( 'Mapped the store checkout into a clean GA4 ecommerce dataLayer', 'Configured Google Ads purchase conversions with transaction values', 'Connected Meta Pixel and Conversions API with event deduplication', 'Tested each event end to end before handover' ),
		),
		array(
			'id'    => 'conversion-tracking',
			'kind'  => 'Online education platform, Australia',
			'title' => 'Conversion Tracking Implementation',
			'desc'  => 'GTM and GA4 tracking for course purchases on a LifterLMS site, so enrolments and revenue show up correctly in analytics and ad reporting.',
			'tags'  => array( 'GTM', 'GA4', 'LifterLMS' ),
			'win'   => array( 'Tag Manager · Tags', array( array( 'GA4 Config', 'Fired', 1 ), array( 'GA4 · purchase', 'Fired', 1 ), array( 'Ads Conversion', 'Fired', 1 ), array( 'Conversion Linker', 'Fired', 1 ) ) ),
			'more'  => array( 'Built a GTM container around the LifterLMS purchase flow', 'Sent course purchases to GA4 as ecommerce events', 'Verified triggers so tags fire once per real purchase', 'Documented the setup for the client team' ),
		),
		array(
			'id'    => 'server-side-tracking',
			'kind'  => 'Ecommerce brand, UK',
			'title' => 'Server-Side Tracking Setup',
			'desc'  => 'A GTM server container on a first-party subdomain forwarding events to GA4, Google Ads and Meta for more durable, privacy-aware measurement.',
			'tags'  => array( 'GTM Server', 'GA4', 'Meta CAPI' ),
			'win'   => array( 'Server Container · Clients', array( array( 'GA4 client', 'Claimed', 2 ), array( 'GA4 tag', 'Sent', 1 ), array( 'Meta CAPI tag', 'Sent', 1 ), array( 'Google Ads tag', 'Sent', 1 ) ) ),
			'more'  => array( 'Deployed a server-side GTM container on a first-party subdomain', 'Routed web events through the server container', 'Forwarded events to GA4, Google Ads and Meta Conversions API', 'Checked requests and payloads in preview mode' ),
		),
	);
}

function pb_case_win( $c ) {
	$o = '<div class="pb-case__shot" aria-hidden="true"><div class="pb-win"><div class="pb-win__bar"><i></i><i></i><i></i><span>' . esc_html( $c['win'][0] ) . '</span></div>';
	foreach ( $c['win'][1] as $r ) {
		$o .= '<div class="pb-row"><code>' . esc_html( $r[0] ) . '</code><span class="st' . ( ! empty( $r[2] ) && 2 === $r[2] ? ' b' : '' ) . '">' . esc_html( $r[1] ) . '</span></div>';
	}
	return $o . '</div></div>';
}

add_shortcode( 'pb_work_cards', function () {
	$o  = '<section class="pb pb-sec pb-work" id="work"><div class="pb-wrap">';
	$o .= pb_sec_head( 'Selected work', 'Real Projects.<br>Real Implementations.', 'A few tracking implementations I have delivered. Client names are kept private.', pb_btn( 'View All Work', home_url( '/work/' ), 'o', 'pb-btn--sm' ) );
	$o .= '<div class="pb-work__grid">';
	foreach ( pb_cases() as $c ) {
		$tags = '';
		foreach ( $c['tags'] as $t ) { $tags .= '<span>' . esc_html( $t ) . '</span>'; }
		$o .= '<article class="pb-case">' . pb_case_win( $c ) . '<div class="pb-case__b"><span class="pb-case__k">' . esc_html( $c['kind'] ) . '</span><h3>' . esc_html( $c['title'] ) . '</h3><p>' . esc_html( $c['desc'] ) . '</p><div class="pb-tags">' . $tags . '</div><a class="pb-link" href="' . esc_url( home_url( '/work/#' . $c['id'] ) ) . '">View Case Study' . pb_ic( 'arrow' ) . '</a></div></article>';
	}
	return $o . '</div></div></section>';
} );

add_shortcode( 'pb_work_full', function () {
	$o = '<section class="pb pb-sec" style="padding-top:20px"><div class="pb-wrap">';
	foreach ( pb_cases() as $c ) {
		$li = '';
		foreach ( $c['more'] as $m ) { $li .= '<li>' . pb_ic( 'check' ) . '<span>' . esc_html( $m ) . '</span></li>'; }
		$tags = '';
		foreach ( $c['tags'] as $t ) { $tags .= '<span>' . esc_html( $t ) . '</span>'; }
		$o .= '<article class="pb-casebig" id="' . esc_attr( $c['id'] ) . '">' . pb_case_win( $c ) . '<div class="pb-casebig__b"><span class="pb-case__k">' . esc_html( $c['kind'] ) . '</span><h2>' . esc_html( $c['title'] ) . '</h2><p>' . esc_html( $c['desc'] ) . '</p><ul>' . $li . '</ul><div class="pb-tags">' . $tags . '</div></div></article>';
	}
	$o .= '<p class="pb-note-box" style="margin-top:32px">Client names and screenshots are shared only with permission. Ask me on a call and I can walk you through a similar setup.</p>';
	return $o . '</div></section>';
} );

add_shortcode( 'pb_profiles', function () {
	$l = pb_links();
	$p = array(
		array( 'fiverr', 'Fiverr', '@ppc_bappi', $l['fiverr'] ),
		array( 'upwork', 'Upwork', 'ppcbappi', $l['upwork'] ),
		array( 'skilluper', 'Skilluper', 'Instructor', $l['skilluper'] ),
		array( 'youtube', 'YouTube', 'PPC Bappi', $l['youtube'] ),
		array( 'linkedin', 'LinkedIn', 'Labib Ahammed Bappi', $l['linkedin'] ),
		array( 'facebook', 'Facebook', '@ppcbappi', $l['facebook'] ),
	);
	$o = '<section class="pb pb-prof" id="profiles"><div class="pb-wrap"><div class="pb-prof__in"><div style="display:flex;flex-direction:column;gap:10px"><span class="pb-eyebrow">Profiles</span><h2>Where You Can Find Me</h2></div><ul>';
	foreach ( $p as $x ) {
		$o .= '<li><a href="' . esc_url( $x[3] ) . '" target="_blank" rel="noopener"><i>' . pb_ic( $x[0] ) . '</i><span><b>' . esc_html( $x[1] ) . '</b><small>' . esc_html( $x[2] ) . '</small></span></a></li>';
	}
	return $o . '</ul></div></div></section>';
} );

function pb_yt_videos() {
	$v = get_transient( 'pb_yt_videos' );
	if ( false !== $v ) { return $v; }
	$v = array();
	$r = wp_remote_get( 'https://www.youtube.com/feeds/videos.xml?channel_id=UCGoDnvlTeg2r2rMYUY9RlGg', array( 'timeout' => 10 ) );
	if ( ! is_wp_error( $r ) && 200 === wp_remote_retrieve_response_code( $r ) ) {
		$xml = @simplexml_load_string( wp_remote_retrieve_body( $r ) );
		if ( $xml ) {
			foreach ( $xml->entry as $e ) {
				$yt    = $e->children( 'http://www.youtube.com/xml/schemas/2015' );
				$title = (string) $e->title;
				if ( ! preg_match( '/track|gtm|tag manager|ga4|analytic|google ads|pixel|conversion|capi|server|cookie|consent|ppc|order|client|setup/i', $title ) || preg_match( '/driving/i', $title ) ) { continue; }
				$tut = preg_match( '/track|gtm|tag manager|ga4|analytic|pixel|conversion|capi|server|cookie|consent|setup/i', $title ) ? 0 : 1;
				$v[] = array( 'id' => (string) $yt->videoId, 'title' => $title, 'p' => $tut, 'i' => count( $v ) );
			}
			usort( $v, function ( $a, $b ) { return $a['p'] === $b['p'] ? $a['i'] - $b['i'] : $a['p'] - $b['p']; } );
			$v = array_slice( $v, 0, 3 );
		}
	}
	set_transient( 'pb_yt_videos', $v, empty( $v ) ? HOUR_IN_SECONDS : 12 * HOUR_IN_SECONDS );
	return $v;
}

add_shortcode( 'pb_youtube', function () {
	$l  = pb_links();
	$v  = pb_yt_videos();
	$o  = '<section class="pb pb-sec pb-yt" id="youtube"><div class="pb-wrap"><div class="pb-yt__grid"><div class="pb-yt__copy"><span class="pb-eyebrow">YouTube</span><h2 class="pb-h2">I Share What I Learn</h2><p class="pb-lead">Practical tutorials and insights about Google Ads, GTM, GA4, conversion tracking and analytics.</p>' . pb_btn( 'Visit My YouTube Channel', $l['yt_home'] ) . '</div><div>';
	if ( $v ) {
		$m  = $v[0];
		$o .= '<a class="pb-yt__main" href="https://www.youtube.com/watch?v=' . esc_attr( $m['id'] ) . '" target="_blank" rel="noopener"><img src="https://i.ytimg.com/vi/' . esc_attr( $m['id'] ) . '/hqdefault.jpg" alt="' . esc_attr( $m['title'] ) . '" loading="lazy"><span class="pb-yt__play">' . pb_ic( 'play' ) . '</span><span class="pb-yt__cap">' . esc_html( $m['title'] ) . '</span></a>';
		if ( count( $v ) > 1 ) {
			$o .= '<div class="pb-yt__list">';
			foreach ( array_slice( $v, 1, 2 ) as $s ) {
				$o .= '<a class="pb-yt__sm" href="https://www.youtube.com/watch?v=' . esc_attr( $s['id'] ) . '" target="_blank" rel="noopener"><img src="https://i.ytimg.com/vi/' . esc_attr( $s['id'] ) . '/mqdefault.jpg" alt="" loading="lazy"><span>' . esc_html( $s['title'] ) . '</span></a>';
			}
			$o .= '</div>';
		}
	} else {
		$o .= '<a class="pb-yt__main" href="' . esc_url( $l['yt_home'] ) . '" target="_blank" rel="noopener" style="display:flex;align-items:center;justify-content:center"><span class="pb-yt__play" style="position:static;transform:none">' . pb_ic( 'play' ) . '</span></a>';
	}
	return $o . '</div></div></div></section>';
} );

add_shortcode( 'pb_process', function () {
	$s = array(
		array( 'Audit', 'Understand the current setup and tracking problems.' ),
		array( 'Plan', 'Define what should be tracked and how.' ),
		array( 'Implement', 'Configure the required tracking systems.' ),
		array( 'Test', 'Verify every event and conversion.' ),
		array( 'Document', 'Provide clear documentation and next steps.' ),
	);
	$o = '<section class="pb pb-sec pb-proc" id="process"><div class="pb-wrap">' . pb_sec_head( 'My process', 'How I Work With Clients', 'A simple and transparent process to get your tracking right.' ) . '<ol class="pb-steps">';
	foreach ( $s as $i => $x ) {
		$o .= '<li><span class="n">' . sprintf( '%02d', $i + 1 ) . '</span><div><h3>' . esc_html( $x[0] ) . '</h3><p>' . esc_html( $x[1] ) . '</p></div></li>';
	}
	return $o . '</ol></div></section>';
} );

add_shortcode( 'pb_blog', function () {
	$q  = new WP_Query( array( 'post_type' => 'post', 'posts_per_page' => 3, 'post_status' => 'publish', 'ignore_sticky_posts' => true, 'no_found_rows' => true ) );
	$pf = get_option( 'page_for_posts' );
	$o  = '<section class="pb pb-sec pb-blog" id="blog"><div class="pb-wrap">' . pb_sec_head( 'Blog & resources', 'Blog &amp; Resources', 'Guides and notes on tracking, analytics and Google Ads.', $q->have_posts() ? pb_btn( 'View All Articles', $pf ? get_permalink( $pf ) : home_url( '/blog/' ), 'o', 'pb-btn--sm' ) : '' );
	if ( $q->have_posts() ) {
		$o .= '<div class="pb-blog__grid">';
		while ( $q->have_posts() ) {
			$q->the_post();
			$cat = get_the_category();
			$img = has_post_thumbnail() ? get_the_post_thumbnail( get_the_ID(), 'medium_large', array( 'loading' => 'lazy', 'alt' => '' ) ) : '';
			$o  .= '<article class="pb-post">' . ( $img ? '<a class="pb-post__img" href="' . esc_url( get_permalink() ) . '">' . $img . '</a>' : '' ) . '<div class="pb-post__b">' . ( $cat ? '<span class="pb-post__cat">' . esc_html( $cat[0]->name ) . '</span>' : '' ) . '<h3><a href="' . esc_url( get_permalink() ) . '">' . esc_html( get_the_title() ) . '</a></h3><p>' . esc_html( wp_trim_words( get_the_excerpt(), 20 ) ) . '</p><div class="pb-post__meta"><span>' . esc_html( get_the_date() ) . '</span><a class="pb-link" href="' . esc_url( get_permalink() ) . '">Read Article' . pb_ic( 'arrow' ) . '</a></div></div></article>';
		}
		wp_reset_postdata();
		$o .= '</div>';
	} else {
		$l  = pb_links();
		$o .= '<div class="pb-empty"><div><h3>New articles are on the way</h3><p>Until then, my tracking tutorials are on YouTube.</p></div>' . pb_btn( 'Watch on YouTube', $l['yt_home'], 'o' ) . '</div>';
	}
	return $o . '</div></section>';
} );

add_shortcode( 'pb_cta', function () {
	$l = pb_links();
	return '<section class="pb pb-cta"><div class="pb-wrap"><div class="pb-cta__box"><div><h2>Something Isn\'t Tracking?<br><span>Let\'s Find Out Why.</span></h2><p>Tell me what you\'re trying to measure and what\'s currently not working. I\'ll take a look and suggest the best way forward.</p></div><div class="pb-cta__btns">' . pb_btn( 'Get a Free Tracking Audit', $l['audit'] ) . pb_btn( 'Send Me a Message', $l['contact'], 'o' ) . '</div></div></div></section>';
} );

add_shortcode( 'pb_contact', function () {
	$sent = isset( $_GET['pb_sent'] ) ? sanitize_key( wp_unslash( $_GET['pb_sent'] ) ) : '';
	$opts = array( '' => 'Select a service', 'tracking-audit' => 'Free Tracking Audit' );
	foreach ( pb_services() as $slug => $s ) { $opts[ $slug ] = $s[0]; }
	$opts['other'] = 'Something else';
	$sel = '';
	foreach ( $opts as $v => $t ) { $sel .= '<option value="' . esc_attr( $v ) . '"' . ( '' === $v ? ' disabled selected' : '' ) . '>' . esc_html( $t ) . '</option>'; }
	$alert = '';
	if ( '1' === $sent ) { $alert = '<div class="pb-alert ok" role="status">Thanks! Your message has been sent. I\'ll get back to you soon.</div>'; }
	if ( 'err' === $sent ) { $alert = '<div class="pb-alert err" role="alert">Please fill in your name, a valid email and a message, then try again.</div>'; }
	$o  = '<section class="pb pb-sec pb-contact" id="contact"><div class="pb-wrap"><div class="pb-contact__grid"><div class="pb-contact__copy"><span class="pb-eyebrow">Contact</span><h2>Let\'s Work Together</h2><p class="pb-lead">Tell me about your project and what you want to measure. I\'ll get back to you as soon as possible.</p><ul class="pb-cinfo"><li><i>' . pb_ic( 'pin' ) . '</i>Based in Bangladesh</li><li><i>' . pb_ic( 'globe' ) . '</i>Available for remote work worldwide</li><li><i>' . pb_ic( 'cal' ) . '</i><a href="' . esc_url( pb_links()['book'] ) . '" style="color:#fff">Prefer a call? Book a time</a></li></ul></div>';
	$o .= '<form class="pb-form" method="post" action="' . esc_url( admin_url( 'admin-post.php' ) ) . '">' . $alert;
	$o .= '<input type="hidden" name="action" value="pb_contact">' . wp_nonce_field( 'pb_contact', 'pb_nonce', true, false ) . '<input type="hidden" name="pb_back" value="' . esc_attr( get_permalink() ) . '">';
	$o .= '<label class="hp" aria-hidden="true">Leave empty<input type="text" name="pb_hp" tabindex="-1" autocomplete="off"></label>';
	$o .= '<label>Full Name *<input type="text" name="name" required autocomplete="name"></label>';
	$o .= '<label>Email Address *<input type="email" name="email" required autocomplete="email"></label>';
	$o .= '<label>Website<input type="text" inputmode="url" name="website" placeholder="yourwebsite.com" autocomplete="url" autocapitalize="off" spellcheck="false"></label>';
	$o .= '<label>Service Needed<select name="service">' . $sel . '</select></label>';
	$o .= '<label class="full">Message *<textarea name="message" required placeholder="What are you trying to track, and what is not working right now?"></textarea></label>';
	$o .= '<div class="full" style="display:flex;gap:16px;align-items:center;flex-wrap:wrap"><button class="pb-btn pb-btn--p" type="submit">Send Message' . pb_ic( 'arrow' ) . '</button><span class="pb-form__note">I reply personally, usually within one business day.</span></div>';
	return $o . '</form></div></div></section>';
} );

/* ---------- Leads + form handler ---------- */
add_action( 'init', function () {
	register_post_type( 'pb_lead', array(
		'labels'       => array( 'name' => 'Leads', 'singular_name' => 'Lead' ),
		'public'       => false,
		'show_ui'      => true,
		'menu_icon'    => 'dashicons-email-alt',
		'supports'     => array( 'title', 'editor' ),
		'capability_type' => 'post',
		'map_meta_cap' => true,
	) );
} );

function pb_handle_contact() {
	$back = isset( $_POST['pb_back'] ) ? esc_url_raw( wp_unslash( $_POST['pb_back'] ) ) : home_url( '/' );
	if ( ! wp_validate_redirect( $back, false ) ) { $back = home_url( '/' ); }
	$ok   = isset( $_POST['pb_nonce'] ) && wp_verify_nonce( sanitize_text_field( wp_unslash( $_POST['pb_nonce'] ) ), 'pb_contact' );
	if ( ! empty( $_POST['pb_hp'] ) ) { wp_safe_redirect( add_query_arg( 'pb_sent', '1', $back ) . '#contact' ); exit; }
	$name  = sanitize_text_field( wp_unslash( $_POST['name'] ?? '' ) );
	$email = sanitize_email( wp_unslash( $_POST['email'] ?? '' ) );
	$site  = trim( sanitize_text_field( wp_unslash( $_POST['website'] ?? '' ) ) );
	if ( '' !== $site && ! preg_match( '#^https?://#i', $site ) ) { $site = 'https://' . ltrim( $site, '/' ); }
	$site  = esc_url_raw( $site );
	$svc   = sanitize_text_field( wp_unslash( $_POST['service'] ?? '' ) );
	$msg   = sanitize_textarea_field( wp_unslash( $_POST['message'] ?? '' ) );
	if ( ! $ok || ! $name || ! is_email( $email ) || ! $msg ) {
		wp_safe_redirect( add_query_arg( 'pb_sent', 'err', $back ) . '#contact' );
		exit;
	}
	$body = "Name: $name\nEmail: $email\nWebsite: $site\nService: $svc\n\n$msg";
	wp_insert_post( array( 'post_type' => 'pb_lead', 'post_status' => 'private', 'post_title' => $name . ' (' . $email . ')', 'post_content' => $body ) );
	$form = ( 'tracking-audit' === $svc ) ? 'Free Tracking Audit' : 'Contact form';
	$page = wp_get_referer() ? wp_get_referer() : $back;
	$body .= "\n\n---\nForm: $form\nPage: $page\nTime: " . wp_date( 'Y-m-d H:i' ) . ' (' . wp_timezone_string() . ')';
	wp_mail( 'ppcbappi@gmail.com', 'New ' . $form . ' lead from ppcbappi.com: ' . $name, $body, array( 'From: PPC BAPPI Website <no-reply@ppcbappi.com>', 'Reply-To: ' . $name . ' <' . $email . '>' ) );
	wp_safe_redirect( add_query_arg( 'pb_sent', '1', $back ) . '#contact' );
	exit;
}
add_action( 'admin_post_nopriv_pb_contact', 'pb_handle_contact' );
add_action( 'admin_post_pb_contact', 'pb_handle_contact' );

/* Blog templates (archive + single) */
require_once __DIR__ . '/pb-blog.inc';
add_action( 'wp_enqueue_scripts', function () {
	$css = WP_CONTENT_DIR . '/uploads/pb/pb-blog.css';
	if ( ( is_home() || is_archive() || is_search() || is_singular( 'post' ) ) && file_exists( $css ) ) {
		wp_enqueue_style( 'pb-blog', content_url( '/uploads/pb/pb-blog.css' ), array( 'pb-site' ), filemtime( $css ) );
	}
}, 30 );
