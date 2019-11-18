import { Router } from "express";
import documentController from "../controllers/DocumentController";

class HomeRoutes {
    public router: Router = Router();
    constructor() {
        this.config();
    }
    config(): void {
        this.router.post("/files", documentController.receive );
    }
}

const DocumentsRouter =  new HomeRoutes();
export default DocumentsRouter.router;