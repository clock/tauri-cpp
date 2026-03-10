import { cpSync, mkdirSync, rmSync, watch } from "node:fs";
import { resolve } from "node:path";

const root_dir = resolve(import.meta.dirname);
const src_dir = resolve(root_dir, "src");
const dist_dir = resolve(root_dir, "dist");
const watch_mode = process.argv.includes("--watch");

const build = () => {
  rmSync(dist_dir, { force: true, recursive: true });
  mkdirSync(dist_dir, { recursive: true });
  cpSync(src_dir, dist_dir, { recursive: true });
  console.log("built plain_html");
};

build();

if (watch_mode) {
  watch(src_dir, { recursive: true }, () => build());
}
