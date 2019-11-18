"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class HomeController {
    index(req, res) {
        res.json({ msg: "hello world" });
    }
}
const homeController = new HomeController();
exports.default = homeController;
