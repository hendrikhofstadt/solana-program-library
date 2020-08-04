extern crate cbindgen;

use std::env;

fn main() {
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    let config = cbindgen::Config {
        header: Some("/* Autogenerated SPL Token program C Bindings */".to_string()),
        after_includes: Some(format!(
            "{}{}{}{}",
            format!(
                "\n#define TOKEN_MAJOR_VERSION {}",
                env!("CARGO_PKG_VERSION_MAJOR")
            ),
            format!(
                "\n#define TOKEN_MINOR_VERSION {}",
                env!("CARGO_PKG_VERSION_MINOR")
            ),
            format!(
                "\n#define TOKEN_PATCH_VERSION {}",
                env!("CARGO_PKG_VERSION_PATCH")
            ),
            "\n\ntypedef uint8_t Token_U256[32];"
        )),
        language: cbindgen::Language::C,
        line_length: 80,
        style: cbindgen::Style::Both,
        tab_width: 4,
        cpp_compat: true,
        pragma_once: true,
        enumeration: cbindgen::EnumConfig {
            prefix_with_name: true,
            ..cbindgen::EnumConfig::default()
        },
        export: cbindgen::ExportConfig {
            prefix: Some("Token_".to_string()),
            include: vec![
                "TokenInstruction".to_string(),
                "Mint".to_string(),
                "Account".to_string(),
                "Multisig".to_string(),
            ],
            ..cbindgen::ExportConfig::default()
        },
        parse: cbindgen::ParseConfig {
            parse_deps: true,
            include: Some(vec![
                "solana-sdk".to_string(),
                "primitive-types".to_string(),
            ]),
            ..cbindgen::ParseConfig::default()
        },
        ..cbindgen::Config::default()
    };
    cbindgen::Builder::new()
        .with_crate(crate_dir)
        .with_config(config)
        .generate()
        .unwrap()
        .write_to_file("inc/token.h");
}
