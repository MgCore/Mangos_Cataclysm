-- Goblins and Worgen
DELETE FROM creature_model_info WHERE modelid in (6894, 6895, 29422, 29423);
INSERT INTO creature_model_info (modelid, bounding_radius, combat_reach, gender, modelid_other_gender, modelid_alternative) VALUES
(6894,  0.306, 1.5, 0, 6895,  0),
(6895,  0.306, 1.5, 1, 6894,  0),
(29422, 0.347, 1.5, 0, 29423, 0),
(29423, 0.347, 1.5, 1, 29422, 0);
