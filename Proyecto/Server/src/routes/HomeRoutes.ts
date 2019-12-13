import { Router } from "express";
import homeController from "../controllers/HomeController";

class HomeRoutes {
    public router: Router = Router();
    constructor() {
        this.config();
    }
    config(): void {
        this.router.get("/", homeController.index );
    }
}

const homeRoutes =  new HomeRoutes();
export default homeRoutes.router;